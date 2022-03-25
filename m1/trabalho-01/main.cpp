#include <iostream>
using namespace std;

#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include "init_graph.h"
#include "menu.h"
#include "graph_func.h"

typedef vector<vector<int>> AdjacencyMatrix;

void clear_screen()
{
#ifdef _WIN32
    std::system("cls");
#else
    // POSIX
    std::system ("clear");
#endif
}

void clear_matrix(int** matrix, int rows)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] = 0;
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

    get_graph_initial_state(adj_mat,is_directed_graph);


    clear_screen();

    do
    {
        print_adjacent_matrix(adj_mat);

        cout << "\n\n";

        print_main_menu();
        selected_menu_option = get_valid_menu_option();

        switch(selected_menu_option)
        {
        case 'a': // add one vertice
            cout << "\n\n";
            vertices_count++;
            add_graph_vertice(adj_mat,is_directed_graph);
            clear_screen();
            break;

        case 'b': // add new edge/arc
            cout << "\n\n";
            get_new_adjacency(adj_mat);
            clear_screen();
            break;

        case 'c': // remove vertice
            cout << "\n\n";
            remove_graph_vertice(adj_mat, get_selected_vertice("Qual vertice voce deseja remover?"));
            clear_screen();
            break;

        case 'd': // remove edge/arc
            cout << "\n\n";
            remove_vertice_adjacency(adj_mat);
            clear_screen();
            break;
        case 'p': // search by depth
        {
            cout << "\n\n";
            vector<int> visiting_order;
            visiting_order = graph_depth_first_search(adj_mat, get_search_type());
            cout << "Ordem de visitacao -> [\t";
            for(int i = 0; i < visiting_order.size(); i++)
            {
                printf("%d\t", visiting_order[i] + 1);
            }

            cout << "\t]\n\n";
            break;
        }

        case 'l': // search by breadth
        {
            cout << "\n\n";
            vector<int> visiting_order;
            visiting_order = graph_depth_breadth_search(adj_mat, get_search_type());
            cout << "Ordem de visitacao -> [\t";
            for(int i = 0; i < visiting_order.size(); i++)
            {
                printf("%d\t", visiting_order[i] + 1);
            }

            cout << "\t]\n\n";
            break;
        }

        case 'q':

            break;

        default:
            cout << "\n\n\n" << selected_menu_option << "\n\n\n";
            printf("\n[!] Opcao invalida\n\n");
            continue;
        }
    }
    while (selected_menu_option != 'q');

    cout << "\to/";

    return 0;
}