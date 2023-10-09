#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Class Node
class Node
{
    public:
    int data;
    int height;
    // Right hand side tree and left hand side tree
    Node *RHS;
    Node *LHS;
};

// Heights of Left anf Right Nodes 
int Level(int Left_Height, int Right_height)
{
    return (max(Left_Height, Right_height) + 1);
}

// Height of a node 
int LevelNode(Node *node)
{
    if (node != NULL)
    {
        return (node->height);
    }
    return (0);
}

// New node - Initialise a node 
Node *newNode(int object)
{
    Node *data = new Node;
    data->data = object;
    data->LHS = NULL;
    data->RHS = NULL;
    data->height = 1;
    return data;
}

// Rotation function 
Node *AVL_Rotation(Node *value_X, int value_Y)
{
    // Left rotation 
    if (value_Y != 1)
    {
        Node *MoveLeft = value_X->LHS;
        Node *MoveLefttoRight = MoveLeft->RHS;

        MoveLeft->RHS = value_X;
        value_X->LHS = MoveLefttoRight;

        value_X->height = Level(LevelNode(value_X->LHS), LevelNode(value_X->RHS));
        MoveLeft->height = Level(LevelNode(MoveLeft->LHS), LevelNode(MoveLeft->RHS));

        return (MoveLeft);
    }
    // Right rotation
    else
    {
        Node *MoveRight = value_X->RHS;
        Node *MoveRighttoLeft = MoveRight->LHS;

        MoveRight->LHS = value_X;
        value_X->RHS = MoveRighttoLeft;

        value_X->height = Level(LevelNode(value_X->LHS), LevelNode(value_X->RHS));
        MoveRight->height = Level(LevelNode(MoveRight->LHS), LevelNode(MoveRight->RHS));

        return (MoveRight);
    }
}

// Finds the largest value node in a subtree and returns it
Node *Largest_sum(Node *node)
{
    if (node->RHS != NULL)
    {
        return Largest_sum(node->RHS);
    }
    return node;
}

// inserts a node and rebalances if required
Node *Push(Node *node, int insert_node)
{
    if (node == NULL)
    {
        return newNode(insert_node);
    }

    if (node->data > insert_node)
    {
        node->LHS = Push(node->LHS, insert_node);
    }
    else if (node->data < insert_node)
    {
        node->RHS = Push(node->RHS, insert_node);
    }
    else
    {
        return (node);
    }

    node->height = Level(LevelNode(node->LHS), LevelNode(node->RHS));
    int balance;

    balance = LevelNode(node->LHS) - LevelNode(node->RHS);

    if (balance > 1)
    {
        if(insert_node < node->LHS->data)
        {
            return AVL_Rotation(node, 2);
        }
        else if (insert_node > node->LHS->data)
        {
            node->LHS = AVL_Rotation(node->LHS, 1);
            return AVL_Rotation(node, 2);
        }
    }
    else if (balance < -1)
    {
        if (insert_node > node->RHS->data)
        {
            return(AVL_Rotation(node, 1));
        }
        else if (insert_node < node->RHS->data)
        {
            node->RHS = AVL_Rotation(node->RHS, 2);
            return AVL_Rotation(node, 1);
        }
    }
    return node;
}

void Post(Node *str)
{
    if (str == NULL)
    {
        return;
    }
    Post(str->LHS);
    Post(str->RHS);
    cout << str->data << " ";
}

void In(Node *str)
{
    if (str == NULL)
    {
        return;
    }
    In(str->LHS);
    cout << str->data << " ";
    In(str->RHS);
}

void Pre(Node *str)
{
    if (str == NULL)
    {
        return;
    }
    cout << str->data << " ";
    Pre(str->LHS);
    Pre(str->RHS);
}

Node *Delete(Node *node, int Num)
{
    if (node == NULL)
    {
        return node;
    }
    else if (Num > node->data)
    {
        node->RHS = Delete(node->RHS, Num);
    }
    else if (Num < node->data)
    {
        node->LHS = Delete(node->LHS, Num);
    }
    else 
    {
        if (node->RHS == NULL && node->LHS == NULL)
        {
            node = NULL;
        }
        else if (node->LHS == NULL)
        {
            node = node->RHS;
        }
        else if (node->RHS == NULL)
        {
            node = node->LHS;
        }
        else 
        {
            node->data = Largest_sum(node->LHS)->data;
            node->LHS = Delete(node->LHS, Largest_sum(node->LHS)->data);
        }
    }
    if (node != NULL)
    {
        node->height = Level(LevelNode(node->LHS), LevelNode(node->RHS));
    }
    else
    {
        return node;
    }

    int balance = LevelNode(node->LHS) - LevelNode(node->RHS);
    int balanceLeft = 0;
    int balanceRight = 0;

    if (node->LHS != NULL)
    {
        balanceLeft = LevelNode(node->LHS->LHS) - LevelNode(node->LHS->RHS);
    }
    if (node->RHS != NULL)
    {
        balanceRight = LevelNode(node->RHS->LHS) - LevelNode(node->RHS->RHS);
    }
    if (balance < -1)
    {
        if (balanceRight <= 0)
        {
            // left rotation 
            return(AVL_Rotation(node, 1));
        }
        // right-left rotation
        else if (balanceRight > 0)
        {
            node->RHS = AVL_Rotation(node->RHS, 2);
            return AVL_Rotation(node, 1);
        }
    }
    else if (balance > 1)
    {
        if (balanceLeft >= 0)
        {
            return AVL_Rotation(node, 2);
        }
        else if (balanceLeft < 0)
        {
            node->LHS = AVL_Rotation(node->LHS, 1);
            return (AVL_Rotation(node, 2));
        }
    }
    return node;
}

int main()
{
    string elements;
    getline(cin, elements);
    char interval = ' ';
    stringstream stream(elements);
   
    string value;
    Node *i = NULL;
    while (getline(stream, value, interval))
    {
        if (value == "IN" || value == "PRE" || value == "POST")
        {
            if (i == NULL)
            {
                cout << "EMPTY";
                break;
            }
            if (value == "IN")
                In(i);
            else if (value == "PRE")
                Pre(i);
            else if (value == "POST")
                Post(i);
            break;
        }

        int Num = stoi(value.substr(1, value.length()));
        if (value.at(0) == 'A')
        {
            //Pushnodes the nodes
            
                i = Push(i, Num);
           
        }
        else if (value.at(0) == 'D')
        {
            // delete the nodes
            i = Delete(i, Num);
        }
    }
    return 0;
}
