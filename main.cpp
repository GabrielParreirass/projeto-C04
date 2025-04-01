#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct item
{
    string nome;
    string nomeDono;
    string propMagica;
    int numIdent;
    int raridade;
};

;

vector<item> inventario;


void inserir_item()
{

    item novoItem;

    cout << "VAMOS INSERIR UM NOVO ITEM:" << endl;
    cout << "" << endl;
    cout << "Insiria o nome do item: ";
    cin >> novoItem.nome;
    cout << "Insiria o nome do dono: ";
    cin >> novoItem.nomeDono;
    cout << "Insira a propriedade magica: ";
    cin >> novoItem.propMagica;
    cout << "Insiria o numero de identificacao: ";
    cin >> novoItem.numIdent;
    cout << "Insiria a raridade: ";
    cin >> novoItem.raridade;

    inventario.push_back(novoItem);
    cout << endl;
    cout << "ITEM ADICIONADO COM SUCESSO!" << endl;
    cout << endl;
};

void cadastrar_similidaridade()
{
    cout << "Funcionalidade em construcao" << endl;
};

void buscar_items()
{
    int tamanhoInventario = inventario.size();

    cout << "ITENS NO INVENTARIO: " << tamanhoInventario << endl;
    cout << "- - - - -" << endl;

    for (int i = 0; i < tamanhoInventario; i++)
    {
        cout << inventario[i].nome << endl;
        cout << "- - - - -" << endl;
    }

    cout << "FIM DO INVENTARIO! " << endl;
};

void verificar_item()
{
    cout << "Funcionalidade em construcao" << endl;
};

void listar_itens_alfabetica()
{
    cout << "Funcionalidade em construcao" << endl;
};

void listar_itens_raridade()
{
    cout << "Funcionalidade em construcao" << endl;
};

void contar_itens_mesma_prop()
{
    cout << "Funcionalidade em construcao" << endl;
}

void remover_itens_menos_raros()
{
    cout << "Funcionalidade em construcao" << endl;
}

int main()
{

    int opcao;

    while (true)
    {
        cout << "" << endl;
        cout << "Escolha uma opcao abaixo: " << endl;
        cout << "1 - inserir item" << endl;
        cout << "2 - cadastrar similaridade" << endl;
        cout << "3 - bucar itens" << endl;
        cout << "4 - verificar itens" << endl;
        cout << "5 - listar itens por ordem alfabetica" << endl;
        cout << "6 - listar itens por raridade" << endl;
        cout << "7 - contar items com a mesma propriedade" << endl;
        cout << "8 - remover itens menos raros" << endl;
        cout << "" << endl;
        cout << "Digite uma opcao: ";
        cin >> opcao;
        cout << "----------------------------" << endl;
        switch (opcao)
        {
        case 1:
            inserir_item();
            break;
        case 2:
            cadastrar_similidaridade();
            break;
        case 3:
            buscar_items();
            break;
        case 4:
            verificar_item();
            break;
        case 5:
            listar_itens_alfabetica();
            break;
        case 6:
            listar_itens_raridade();
            break;
        case 7:
            contar_itens_mesma_prop();
            break;
        case 8:
            remover_itens_menos_raros();
            break;
        default:
            break;
        }
        cout << "----------------------------" << endl;
    }

    return 0;
}
