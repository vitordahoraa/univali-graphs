#include <iostream>
using namespace std;
#include <vector>

#include <string>
#include <sstream>

typedef vector<vector<int>> AdjacencyMatrix;

void clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // POSIX
    std::system ("clear");
#endif
}

string get_graph_type()
{
    char user_answer;

    cout << "O grafo é direcionado (y/n)? ";
    cin >> user_answer;

    user_answer = tolower(user_answer);

    return user_answer == 'y' ? "directed" : "non-directed";
}

int get_vertices_count()
{
    int vertices;

    cout << "O grafo tem quantos vertices? ";
    cin >> vertices;

    return vertices;
}

void clear_matrix(int** matrix, int rows)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] = 0;
}

bool is_adjacent_vertices(AdjacencyMatrix matrix, int i, int j)
{
    return matrix[i][j] == 1;
}

bool is_matrix_empty(int** matrix, int rows)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            if(matrix[i][j] == 1) return false;

    return true;
}

void print_adjacent_matrix_row(AdjacencyMatrix matrix, int i)
{
    printf("[ %d ] => ", i + 1);
    for(int j = 0; j < matrix.size(); j++)
    {
        if(is_adjacent_vertices(matrix, i, j))
            printf("%d\t", j + 1);
    }
}

void print_adjacent_matrix(AdjacencyMatrix matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        print_adjacent_matrix_row(matrix, i);
        printf("\n");
    }
}

void print_main_menu()
{
    cout << "Escolha uma opção: \n";
    cout << "[ 1 ] Incluir vertice \n";
    cout << "[ 2 ] Incluir aresta/arco \n";
    cout << "[ 3 ] Remover vertice \n";
    cout << "[ 4 ] Remover aresta/arco \n";
}

bool validate_selected_menu_option(char option)
{
    return
        option == '1'
        || option == '2'
        || option == '3'
        || option == '4'
        || option == 'q';
}

char get_valid_menu_option()
{
    char selected_option;
    bool is_valid_option;

    do
    {
        cout << "~ ";
        cin >> selected_option;

        selected_option = tolower(selected_option);

        is_valid_option = validate_selected_menu_option(selected_option);
        if(!is_valid_option) cout << "[!] Opcao invalida\n\n";
    }
    while (!is_valid_option);

    return selected_option;
}

void set_graph_vertice(AdjacencyMatrix &matrix, int vertice, vector<int> adjacency_list)
{
    for(int i = 0; i < adjacency_list.size(); i++)
        matrix[vertice][adjacency_list[i] - 1] = 1;

}

vector<int> get_vertice_adjacency_list(int vertice, int vertices_count) {
    string adjacent_vertices;
    string adjacent_vertice_as_string;
    int adjacent_vertice;

    vector<int> adjacency_list;

    // BUG: the adjacency list needs to begin with a whitespace
    printf("Digite os vertices adjacentes ao vertice %d, separados por espacos (ex: 2 5 9)\n", vertice + 1);
    printf("~ ");

    std::cin.get();
    std::getline(std::cin, adjacent_vertices);

    // adjacent_vertices is a string with the pattern "1 2 3", where each number represents one adjacent vertice of i
    std::istringstream iss(adjacent_vertices);

    while(iss >> adjacent_vertice_as_string)
    {
        adjacent_vertice = stoi(adjacent_vertice_as_string);

        if (adjacent_vertice > vertices_count) continue;

        adjacency_list.push_back(adjacent_vertice);
    }

    return adjacency_list;
}

void get_graph_initial_state(AdjacencyMatrix &matrix)
{
    string adjacent_vertices;
    string vertice;

    vector<int> vertice_adjacency_list;

    for(int i = 0; i < matrix.size(); i++)
    {
        vertice_adjacency_list = get_vertice_adjacency_list(i, matrix.size());

        cout << endl;

        set_graph_vertice(matrix, i, vertice_adjacency_list);
    }
}

void add_graph_vertice(AdjacencyMatrix &adjacent_matrix)
{

}

int main()
{
    bool is_directed_graph;
    int vertices_count;
    char selected_menu_option;

    is_directed_graph = get_graph_type() == "directed";
    vertices_count = get_vertices_count();

    AdjacencyMatrix adj_mat(vertices_count, vector<int>(vertices_count, 0));

    cout << "\n\n";

    get_graph_initial_state(adj_mat);

    do
    {
        clear_screen();

        print_adjacent_matrix(adj_mat);
        selected_menu_option = 'q';

        cout << "\n\n";

        print_main_menu();
        selected_menu_option = get_valid_menu_option();

        switch(selected_menu_option)
        {
        case '1': // add one vertice
            vertices_count++;
            add_graph_vertice(adj_mat);
            break;
        }
    }
    while (selected_menu_option != 'q');

    return 0;
}
