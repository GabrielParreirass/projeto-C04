#include <iostream>
#include <string>
#include <vector>
#include <list>
#define nullptr NULL
using namespace std;

struct item
{
    string nome;
    string nomeDono;
    string propMagica;
    int numIdent;
    int raridade;
};

struct Aresta
{
    int origem, destino, peso;
};
struct Node
{
    item dado;
    Node *esquerda;
    Node *direita;
};
struct NodeAlfabetica
{
    item dados;
    NodeAlfabetica *esquerda;
    NodeAlfabetica *direita;
};

Node *raiz = nullptr;

vector<item> inventario;
list<Aresta> grafo[1000];

NodeAlfabetica *inserirPorNome(NodeAlfabetica *raiz, item novoItem)
{
    if (raiz == NULL)
    {
        NodeAlfabetica *novoNo = new NodeAlfabetica;
        novoNo->dados = novoItem;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if (novoItem.nome < raiz->dados.nome)
        raiz->esquerda = inserirPorNome(raiz->esquerda, novoItem);
    else
        raiz->direita = inserirPorNome(raiz->direita, novoItem);

    return raiz;
}

void listarEmOrdemAlfabetica(NodeAlfabetica *raiz)
{
    if (raiz != NULL)
    {
        listarEmOrdemAlfabetica(raiz->esquerda);
        cout << "Item: " << raiz->dados.nome << endl;
        cout << "Dono: " << raiz->dados.nomeDono << endl;
        cout << "Propriedade: " << raiz->dados.propMagica << endl;
        cout << "Raridade: " << raiz->dados.raridade << endl;
        cout << "-------------------------" << endl;
        listarEmOrdemAlfabetica(raiz->direita);
    }
}

void listar_itens_ordem_alfabetica()
{
    if (inventario.empty())
    {
        cout << "Nenhum item no inventario." << endl;
        return;
    }

    NodeAlfabetica *raiz = NULL;

    // Inserir todos os itens do inventário na árvore
    for (size_t i = 0; i < inventario.size(); i++)
    {
        raiz = inserirPorNome(raiz, inventario[i]);
    }

    cout << "ITENS ORDENADOS POR ORDEM ALFABETICA:" << endl;
    cout << "-------------------------------------" << endl;

    listarEmOrdemAlfabetica(raiz);
}

Node *buscar_na_arvore(Node *raiz, int numIdent)
{
    if (raiz == nullptr || raiz->dado.numIdent == numIdent)
        return raiz;

    if (numIdent < raiz->dado.numIdent)
        return buscar_na_arvore(raiz->esquerda, numIdent);
    else
        return buscar_na_arvore(raiz->direita, numIdent);
}

void visualizar_similaridades()
{
    for (int i = 0; i < 1000; i++)
    {
        if (!grafo[i].empty())
        {
            cout << "Item " << i << " tem similaridades com: ";
            for (list<Aresta>::iterator it = grafo[i].begin(); it != grafo[i].end(); it++)
            {
                cout << "[" << it->destino << " (S=" << it->peso << ")] ";
            }
            cout << endl;
        }
    }
}

void cadastrar_similaridade()
{
    int codigoItem1, codigoItem2, similaridade;
    char continuar;
    char verSimilaridades;
    int tamanhoInventario = inventario.size();

    cout << "CADASTRAR SIMILARIDADE ENTRE ITENS" << endl;
    cout << "---------------------------------" << endl;

    do
    {
        cout << "Digite o codigo do primeiro item: ";
        cin >> codigoItem1;
        cout << "Digite o codigo do segundo item: ";
        cin >> codigoItem2;
        cout << "Digite o valor de similaridade (S) entre eles: ";
        cin >> similaridade;

        bool item1Existe = false, item2Existe = false;
        for (int i = 0; i < tamanhoInventario; i++)
        {
            if (inventario[i].numIdent == codigoItem1)
                item1Existe = true;
            if (inventario[i].numIdent == codigoItem2)
                item2Existe = true;
        }

        if (!item1Existe || !item2Existe)
        {
            cout << "ERRO: Um ou ambos os itens nao existem no inventario!" << endl;
            continue;
        }

        Aresta aresta1;
        aresta1.origem = codigoItem1;
        aresta1.destino = codigoItem2;
        aresta1.peso = similaridade;

        Aresta aresta2;
        aresta2.origem = codigoItem2;
        aresta2.destino = codigoItem1;
        aresta2.peso = similaridade;

        grafo[codigoItem1].push_back(aresta1);
        grafo[codigoItem2].push_back(aresta2);

        cout << "Similaridade cadastrada com sucesso!" << endl;
        cout << "Deseja cadastrar outra similaridade? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');
    cout << endl;
    cout << "Deseja ver a lista de itens similares? (s/n): ";
    cin >> verSimilaridades;
    if (verSimilaridades == 's' || verSimilaridades == 'S')
    {
        cout << endl;
        cout << "LISTA DE SIMILARIDADES" << endl;
        visualizar_similaridades();
    }
}

void inserir_item()
{
    item novoItem;
    cout << "VAMOS INSERIR UM NOVO ITEM:" << endl;
    cout << "" << endl;
    cout << "Insira o nome do item: ";
    cin >> novoItem.nome;
    cout << "Insira o nome do dono: ";
    cin >> novoItem.nomeDono;
    cout << "Insira a propriedade magica: ";
    cin >> novoItem.propMagica;
    cout << "Insira o numero de identificacao: ";
    cin >> novoItem.numIdent;
    cout << "Insira a raridade: ";
    cin >> novoItem.raridade;
    inventario.push_back(novoItem);
    cout << endl;
    cout << "ITEM ADICIONADO COM SUCESSO!" << endl;
    cout << endl;
};

void buscar_items()
{
    int tamanhoInventario = inventario.size();

    cout << "ITENS NO INVENTARIO: " << tamanhoInventario << endl;
    cout << "- - - - -" << endl;

    for (int i = 0; i < tamanhoInventario; i++)
    {
        cout << "Item: " << inventario[i].nome << endl;
        cout << "Dono: " << inventario[i].nomeDono << endl;
        cout << "Propriedade: " << inventario[i].propMagica << endl;
        cout << "Raridade: " << inventario[i].raridade << endl;
        cout << "- - - - -" << endl;
    }

    cout << "FIM DO INVENTARIO! " << endl;
};

void verificar_item()
{
    string nomeJogador;
    int codigoItemC, valorSimilaridadeX;
    int tamanhoInventario = inventario.size();

    cout << "VERIFICAR ITENS SIMILARES" << endl;
    cout << "------------------------" << endl;
    cout << "Digite o nome do jogador que nao pertence os itens: ";
    cin >> nomeJogador;
    cout << "Digite o codigo do item que vai ser comparado: ";
    cin >> codigoItemC;
    cout << "Digite o valor minimo de similaridade: ";
    cin >> valorSimilaridadeX;

    // Verificar se o item C existe
    bool itemCExiste = false;
    for (int i = 0; i < tamanhoInventario; i++)
    {
        if (inventario[i].numIdent == codigoItemC)
        {
            itemCExiste = true;
            break;
        }
    }

    if (!itemCExiste)
    {
        cout << "ERRO: Item C nao encontrado no inventario!" << endl;
        return;
    }

    cout << endl
         << "ITENS SIMILARES:" << endl;
    cout << "----------------" << endl;

    bool encontrouSimilar = false;

    for (list<Aresta>::iterator it = grafo[codigoItemC].begin(); it != grafo[codigoItemC].end(); it++)
    {
        if (it->peso > valorSimilaridadeX)
        {
            for (int i = 0; i < tamanhoInventario; i++)
            {
                if (inventario[i].numIdent == it->destino && inventario[i].nomeDono != nomeJogador)
                {
                    cout << "Item: " << inventario[i].nome << endl;
                    cout << "Dono: " << inventario[i].nomeDono << endl;
                    cout << "Similaridade: " << it->peso << endl;
                    cout << "----------------" << endl;
                    encontrouSimilar = true;
                    break;
                }
            }
        }
    }

    if (!encontrouSimilar)
    {
        cout << "Nenhum item encontrado com os criterios especificados." << endl;
    }
}

void listar_itens_alfabetica()
{
    listar_itens_ordem_alfabetica();
}

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
        cout << "9 - sair do inventario" << endl;
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
            cadastrar_similaridade();
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
        case 9:
            cout << endl;
            cout << "OBRIGADO POR UTILIZAR O INVENTARIO, ATE A PROXIMA! :)" << endl;
            cout << endl;
            return 0;
            break;
        default:
            break;
        }
        cout << "----------------------------" << endl;
    }

    return 0;
}
