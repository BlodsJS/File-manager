#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <sstream>
namespace fs = std::filesystem;
using namespace std;

// ----------------- statements global variables -----------------

// ----------------- statements theme variables -----------------
const string current_theme = "default";
const string path_theme = "/home/blods/.Lunarys-ex/themes/";

// ----------------- statements view variables -----------------
const int LARGURA = 80;

// ----------------- statements functions -----------------
void titulo(const string& texto );
void navegar(string caminho);
void path_title(const string& texto, string mode);
void listar_diretorio(const string& caminho);
void conteudo(const string& texto, const string& type);
string linha_esquerda(const string& texto, int reduce);
void linha_horizontal();
string menu_choice();
void view_file(string path);

// ----------------- initial menu -----------------
string menu_choice() {
    string choice;
    cout << "> 1. Travel \n"
         << "> 2. Config \n"
         << "> 3. Quit \n ";
    getline(cin, choice);
    return choice;
}
string creation_menu() {
    string choice;
    cout << "> 1. View file: name of file\n"
         << "> 2. Travel folder: name of folder\n"
         << "> 3. Create\n"
         << "> 4. Delete\n"
         << "> 5. Read mode\n"
         << "> 6. Quit: q\n ";
    getline(cin, choice);
    return choice;
}
string read_menu() {
    string choice;
    cout << "> 1. View file: name of file\n"
         << "> 2. Travel folder: name of folder (1 level)\n"
         << "> 3. Create mode\n"
         << "> 4. Quit: q\n ";
    getline(cin, choice);
    return choice;
}
// ----------------- Mode function -----------------

void create_mode(string caminho) {
    while (true) {
        string choice;
        cout << "\033[2J\033[H";
        titulo("Lunaris File");
        path_title(caminho, "C");
        listar_diretorio(caminho);
        choice = creation_menu();

        if (choice == "5" || choice == "Read" || choice == "Read mode") {
            break;
        } else if (choice == "..") {
            caminho = fs::path(caminho).parent_path().string();
        } else if (choice == "3" || choice == "create" || choice == "create mode") {
            create_mode(caminho);
        } else {
            fs::path novo = fs::path(caminho) / choice;

            if (!fs::is_directory(novo)) {
                view_file(novo);

            } else if (fs::is_directory(novo)) {
                caminho = novo.string();
            }
        }
    }

}

void read_mode(string caminho) {
    while (true) {
        string choice;
        cout << "\033[2J\033[H";
        titulo("Lunaris File");
        path_title(caminho, "R");
        listar_diretorio(caminho);
        choice = read_menu();

        if (choice == "q" ||choice == "4") {
            break;
        } else if (choice == "..") {
            caminho = fs::path(caminho).parent_path().string();
        } else if (choice == "3" || choice == "create" || choice == "create mode") {
            create_mode(caminho);
        } else {
            fs::path novo = fs::path(caminho) / choice;

            if (!fs::is_directory(novo)) {
                view_file(novo);

            } else if (fs::is_directory(novo)) {
                caminho = novo.string();
            }
        }
    }


}
// ---------------- view functions -----------------

string formatLine(int id, const string& content) {
    ostringstream oss;

    oss << "["
        << setw(4)
        << setfill(' ')
        << id
        << "] ";

    // Limita o texto a 60 caracteres
    oss << content.substr(0, 52);

    return oss.str();
}

void linha_horizontal() {
    cout << "+" << string(LARGURA, '-') << "+\n";
}

void titulo(const string& texto) {
    int espacos = LARGURA - texto.size();
    int esq = espacos / 2;
    int dir = espacos - esq;
    linha_horizontal();
    cout << "|"
         << string(esq, ' ')
         << texto
         << string(dir, ' ')
         << "|\n";
         linha_horizontal();
}

void path_title(const string& texto, string mode) {
    int espacos = LARGURA - texto.size();
    int dir = espacos - 10;
    linha_horizontal();
    cout << "| Path [" <<mode <<"]: "
         << texto
         << string(dir, ' ')
         << "|\n";
         linha_horizontal();
}
string linha_esquerda(const string& texto, int reduce) {
    if (texto.size() >= LARGURA)
        return texto.substr(0, LARGURA);

    return texto + string(LARGURA - texto.size() - reduce, ' ');
}

void conteudo(const string& texto, const string& type) {
    if (type == "pass") {
        cout << "|" << linha_esquerda(texto, 0) << "|\n";
        return;
    }
    cout << "|[" <<type << "]" << linha_esquerda(texto, 3) << "|\n";
}

// ----------------- core app -----------------
void listar_diretorio(const string& caminho) {


    for (const auto& entrada : fs::directory_iterator(caminho)) {
        string type;
        if (entrada.is_directory()) {
            type = "D";
        } else {
            type = "F";
        }

        conteudo(entrada.path().filename().string(), type);
    }
    conteudo(" ", "pass");
    linha_horizontal();
}

// ----------------- files functions -----------------
void create_file() {
    cout << "Criação de arquivos";
}
void view_file(string path) {
    cout << "\033[2J\033[H";
    ifstream file(path);
    string line;
    titulo(path);
    int line_number = 0;
    while (getline(file, line)) {
        line_number += 1;
        cout << formatLine(line_number, line) <<"\n";

    }
    linha_horizontal();
    cout << "\n >";
    string _;
    getline(cin, _);

}
void delete_file() {
    cout << "Exclusão de arquivos";
}
// ----------------- folders function -----------------
void create_folder() {
    cout << "Criação de pastas";
}

void edit_folder() {
    cout << "Edição de pastas";
}

void delete_folder() {
    cout << "Exclusão de pastas";
}

// ----------------- initial functions -----------------
void core_folders() {
    fs::path base = fs::path(getenv("HOME")) / ".config/Lunarys";

    fs::create_directories(base / "themes");
    fs::create_directories(base / "logs");
}
//
int main(int argc, char* argv[]) {
    core_folders();
    string caminho = "/home/blods/";
    string choice;

    if (argc > 1) {
        caminho = argv[1];
    }
    if (!fs::exists(caminho)) {
        cout << "Diretório não existe.\n";
        return 1;
    }
    while (true) {
        cout << "\033[2J\033[H";
        titulo("Lunaris File");
        choice = menu_choice();

        if (choice == "q"||choice == "Q"||choice == "Quit" ||choice == "3") {
             cout << "Encerrando App \n";
             break;
        } else if (choice == "config" || choice == "2" ){
            string _;
            cout << "Feature not avaiable...  press enter for return the main menu\n ";
            getline(cin, _);
        } else {
            read_mode(caminho);
        }
    }
    return 0;
}
