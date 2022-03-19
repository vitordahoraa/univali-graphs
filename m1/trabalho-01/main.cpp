#include <iostream>
using namespace std;

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

int** create_empty_matrix(int vertices_count)
{
    int** matrix = new int*[vertices_count];

    for (int i = 0; i < vertices_count; ++i)
        matrix[i] = new int[vertices_count];

    clear_matrix(matrix, vertices_count);

    return matrix;
}

bool is_adjacent_vertices(int** matrix, int i, int j)
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

void print_adjacent_matrix(int** matrix, int vertices_count)
{
    if(is_matrix_empty(matrix, vertices_count))
    {
        cout << "[!] Sua matriz esta vazia";
        return;
    }

    for(int i = 0; i < vertices_count; i++)
    {
        printf("[ %d ] => ", i + 1);
        for(int j = 0; j < vertices_count; j++)
        {
            if(is_adjacent_vertices(matrix, i, j))
                printf("%d\t", j + 1);
        }
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

    do {
        cout << "~ ";
        cin >> selected_option;

        selected_option = tolower(selected_option);

        is_valid_option = validate_selected_menu_option(selected_option);
        if(!is_valid_option) cout << "[!] Opcao invalida\n\n";
    } while (!is_valid_option);

    return selected_option;
}

int main()
{
    bool is_directed_graph;
    int vertices_count;
    int** adj_mat;
    char selected_menu_option;

    is_directed_graph = get_graph_type() == "directed";
    vertices_count = get_vertices_count();

    adj_mat = create_empty_matrix(vertices_count);

    do
    {
        clear_screen();

        print_adjacent_matrix(adj_mat, vertices_count);
        cout << "\n\n";

        print_main_menu();
        selected_menu_option = get_valid_menu_option();
    }
    while (selected_menu_option != 'q');



    return 0;
}
