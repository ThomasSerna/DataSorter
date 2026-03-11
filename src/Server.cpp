#include "../include/Server.h"

void Server::run(int port) {
    setUpRoutes();
    app.loglevel(crow::LogLevel::Warning);
    app.port(port).multithreaded().run();
}

void Server::setUpRoutes() {
    crow::mustache::set_global_base("../templates");

    std::filesystem::create_directories("uploads");
    std::filesystem::create_directories("output");

    // Main page: GET /
    CROW_ROUTE(app, "/")([]() {
        auto page = crow::mustache::load("index.html");
        return page.render();
    });

    // Endpoint: GET /api/health
    CROW_ROUTE(app, "/api/health")([] {
        return "todo melo";
    });

    // Endpoint: POST /api/sort?algorithm=name
    CROW_ROUTE(app, "/api/sort").methods(crow::HTTPMethod::Post)(
        [](const crow::request& req) -> crow::response {

            // Leer queryParam ?algorithm y asignarlo a variable
            auto algorithmParam = req.url_params.get("algorithm");
            std::string algorithm = algorithmParam ? algorithmParam : "all";

            // Obtener el archivo enviado por el usuario
            crow::multipart::message msg(req);
            auto it = msg.part_map.find("file");

            // Error si no encuentra el archivo
            if (it == msg.part_map.end()) {
                SortResponseDto err;
                err.success        = false;
                err.message        = "No se encontró el archivo en el campo 'file'";
                err.algorithm      = algorithm;
                err.outputFilePath = "";
                err.durationMs     = 0.0;
                err.totalWords     = 0;
                return crow::response(400, err.toJson());
            }

            // Se crea un Timestamp para nombrar al archivo
            std::string timestamp = std::to_string(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()
                ).count()
            );

            // Nombrar el archivo
            std::string inputFilename = "file_" + timestamp + ".txt";
            std::string inputPath     = "uploads/" + inputFilename;
            std::ofstream inputFile(inputPath);

            // Control de errores
            if (!inputFile.is_open()) {
                SortResponseDto err;
                err.success        = false;
                err.message        = "No se pudo guardar el archivo recibido";
                err.algorithm      = algorithm;
                err.outputFilePath = "";
                err.durationMs     = 0.0;
                err.totalWords     = 0;
                return crow::response(500, err.toJson());
            }

            // Se guarda la informacion en el archivo localizado en uploads
            inputFile << it->second.body;
            inputFile.close();

            // Sorter ordena y guarda el archivo dependiendo del metodo enviado
            Sorter sorter;
            SortResponseDto result = sorter.sort(inputPath,algorithm);
            const int statusCode = result.success ? 200 : 500;

            // Se envia la respuesta del api
            return crow::response(statusCode, result.toJson());
    });

    // Endpoint: POST /api/download?file=fileName.txt
    CROW_ROUTE(app, "/api/download")(
        [](const crow::request& req) -> crow::response {

            // Leer queryParam ?file y asignarlo a variable
            auto file_param = req.url_params.get("file");
            if (!file_param) {
                return crow::response(400, "Parámetro 'file' requerido");
            }
            std::string filename = std::string(file_param);

            // Prevenir path traversal
            if (filename.find("..") != std::string::npos ||
                filename.find('/')  != std::string::npos ||
                filename.find('\\') != std::string::npos) {
                return crow::response(400, "Nombre de archivo inválido");
            }

            // Se busca y abre el archivo a descargar
            std::string filepath = "output/" + filename;
            std::ifstream inFile(filepath, std::ios::binary);

            // Control de errores
            if (!inFile.is_open()) {
                return crow::response(404, "Archivo no encontrado: " + filename);
            }

            // Se escribe el archivo dentro del buffer para ser enviado
            std::ostringstream buffer;
            buffer << inFile.rdbuf();
            inFile.close();

            // Se envia el archivo desde el api
            crow::response res(200, buffer.str());
            res.set_header("Content-Type",        "text/plain; charset=utf-8");
            res.set_header("Content-Disposition", "attachment; filename=\"" + filename + "\"");
            return res;
    });
}