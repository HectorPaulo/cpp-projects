#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    std::string url;
    std::string format;
    std::string filename;

    std::cout << "Dame la URL del video de YouTube: ";
    std::getline(std::cin, url);

    std::cout << "¿Quieres descargar video (mp4) o solo audio (mp3)? ";
    std::getline(std::cin, format);

    std::cout << "¿Cómo quieres que se llame el archivo (sin extensión)? ";
    std::getline(std::cin, filename);

    std::string command;

    if (format == "mp4") {
        // Descarga el video en mp4
        command = "yt-dlp -f bestvideo[ext=mp4]+bestaudio[ext=m4a]/mp4 "
                  "--merge-output-format mp4 "
                  "-o \"" + filename + ".%(ext)s\" \"" + url + "\"";
    } else if (format == "mp3") {
        // Descarga solo audio y lo convierte a mp3
        command = "yt-dlp -f bestaudio "
                  "--extract-audio --audio-format mp3 "
                  "-o \"" + filename + ".%(ext)s\" \"" + url + "\"";
    } else {
        std::cerr << "Formato no válido. Solo se permite 'mp4' o 'mp3'.\n";
        return 1;
    }

    std::cout << "\nEjecutando comando: " << command << "\n\n";
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "\n✅ Descarga completada con éxito.\n";
    } else {
        std::cout << "\n❌ Ocurrió un error al descargar el video.\n";
    }

    return 0;
}
