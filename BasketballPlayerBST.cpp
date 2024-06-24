// Luis M. Villalobos (1224922959)
// CSE310 - HW4 Question 2 "Basketball Player Statistics"
// NOTE: b) Delete a Player, I implemented but by using the player's stats and not name
//   and e) List names of players with triple doubles, I didn't really comprehend what "when a player log 10 
//           or more of three statistical categories" meant so I really didn't try it. 

#include <iostream>
#include <cstdlib>
using namespace std;

class BinarySearchTree
{
    private:
    class node
    {
    public:
        node* left;
        node* right;
        node* parent;
        int key;
        string Pname;
        string Tname;
    };

    public:
        node* root;
        BinarySearchTree()
        {
        root = NULL;
        }
        node* tripledouble[];

        bool isEmpty() const { return root == NULL; }
        void TREE_INSERT(string, string, int);
        node* FINDMIN(node*);
        void TRANSPLANT(node*, node*);
        void DELETEPLAYER(node*, int);
        void DESCENDING_WALK(node*);
        void TRIPLEDOUBLECHECK(node*);
        void DISPLAYMAXPTS(node*);
        void DISPLAYMAXASTS(node*);
        void DISPLAYMAXREBS(node*);
        void DISPLAYLOWPTS(node*);
        void DISPLAYLOWASTS(node*);
        void DISPLAYLOWREBS(node*);
};

void BinarySearchTree::TREE_INSERT(string playerName, string teamName, int stat)
{
    // This implements the algorithm in page 261 of the textbook
    node* z = new node();
    z->Pname = playerName;
    z->Tname = teamName;
    z->key = stat;
    z->left = NULL;
    z->right = NULL;
    node* y = NULL;
    node* x = root;
    node* parent = NULL;

    while (x != NULL)
    {   
    y = x;
    if (z->key < x->key)
    x = x->left;
    else
    x = x->right;
    }

    z->parent = y;
    if (y == NULL)
    root = z;
    else if (z->key < y->key)
    y->left = z;
    else
    y->right = z;
}

BinarySearchTree::node* BinarySearchTree::FINDMIN(node* x) //  FINDMIN function that returns the node and not the key
{
     while (x->left != NULL) //  go all the way to the left until it points to NULL to find min player
    {
        x = x->left;
    }
    return x;
}

void BinarySearchTree::TRANSPLANT(node* u, node* v) // TRANSPLANT function is a helper to perfrom deletion of a player
{
    // this code is directly taken from the book's TRANSPLANT function
    // the motive of this function is to help the tree keep its structure when deleting a node
    if (u->parent == NULL)
    {
        root = v;
    }

    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }

    else 
    {
        u->parent->right = v;
    }

    if (v != NULL)
    {
        v->parent = u->parent;
    }
}

void BinarySearchTree::DELETEPLAYER(node* x, int stat) // DELETEPLAYER removes the player inputed by user 
{
    // searching for the node that has the key the user inputted:
    while (x != NULL)
    {
        if (stat < x->key)
        {
            x = x->left;
        }

        else if (stat > x->key)
        {
            x = x->right;
        }

        else
        {
            break;
        }
    }

    // if none of the nodes in our BST contain the key, then just notify user
    if (x == NULL)
    {
        cout << "Key doesn't exist " << endl;
    }

    

    if (x->left == NULL)
    {
        TRANSPLANT(x, x->right); // call Transplant
    }

    else if (x->right == NULL)
    {
        TRANSPLANT(x, x->left); // call Transplant
    }

    else
    {
        node* y = new node(); // helper node to delete
        y = FINDMIN(x->right);

        if (y != x->right)
        {
            TRANSPLANT(x, x->right);
            y->right = x->right;
            y->right->parent = y;
        }

        TRANSPLANT(x, y);
        y->left = x->left;
        y->left->parent = y;
    }
}

void BinarySearchTree::DESCENDING_WALK(node* x) // DESCENDING_WALK is a reverse in-order traversal
{
    if (x != NULL)
    {
    if (x->right) DESCENDING_WALK(x->right); // start from x->right 
    cout << " " << x->Pname << " (" << x->Tname << ") " << x->key << "pts , ";
    if (x->left) DESCENDING_WALK(x->left); // ends by x-> left to get the descending order of the BST
    }
}

void BinarySearchTree::TRIPLEDOUBLECHECK(node* x)
{
    
    
}

void BinarySearchTree::DISPLAYMAXPTS(node* x) // DISPLAYMAXPTS finds the player with highest points and prints his info
{
    while (x->right != NULL) // if BST has right subtree, go through it until we find NULL
    {
        x = x->right; // x is going through the greater keys to get to the max
    }
    cout << "Player with the Most Points: " << x->Pname << " who plays for the " << x->Tname << "'s scored " << x->key << " points " << endl;
}   

void BinarySearchTree::DISPLAYMAXASTS(node* x) // DISPLAYMAXASTS finds the player with highest # of assits and prints his info
{
    while (x->right != NULL) // if BST has right subtree, go through it until we find NULL
    {
        x = x->right; // x is going through the greater keys to get to the max
    }
    cout << "Player with the Most Assists: " << x->Pname << " who plays for the " << x->Tname << "'s assisted " << x->key << " times " << endl;
}  

void BinarySearchTree::DISPLAYMAXREBS(node* x) // DISPLAYMAXREBS finds the player with highest # of rebs and prints his info
{
    while (x->right != NULL) // if BST has right subtree, go through it until we find NULL
    {
        x = x->right; // x is going through the greater keys to get to the max
    }
    cout << "Player with the Most Rebounds: " << x->Pname << " who plays for the " << x->Tname << "'s rebounded the ball " << x->key << " times " << endl;
}  

void BinarySearchTree::DISPLAYLOWPTS(node* x)
{
    while (x->left != NULL) // if BST has left subtree, go thorugh it until left points to null
    {
        x = x->left; // traverse through the left
    }
    cout << "Player with the Least Points: " << x->Pname << " who plays for the " << x->Tname << "'s scored " << x->key << " points " << endl;
}

void BinarySearchTree::DISPLAYLOWASTS(node* x)
{
    while (x->left != NULL) // if BST has left subtree, go thorugh it until left points to null
    {
        x = x->left; // traverse through the left
    }
    cout << "Player with the Least Assists: " << x->Pname << " who plays for the " << x->Tname << "'s assisted " << x->key << " times " << endl;
}

void BinarySearchTree::DISPLAYLOWREBS(node* x)
{
    while (x->left != NULL) // if BST has left subtree, go thorugh it until left points to null
    {
        x = x->left; // traverse through the left
    }
    cout << "Player with the Least Rebounds: " << x->Pname << " who plays for the " << x->Tname << "'s rebounded the ball " << x->key << " times " << endl;
}

int main()
{
    BinarySearchTree pointsBST, assistBST, reboundsBST;
    char choice;
    string playerName, teamName; // string to hold the players name
    int numPoints, numAssists, numRebounds; // int to hold player stats


    while (true)
    {
    cout << endl << endl;
    cout << " Welcome to Basketball Player Statistics BST " << endl;
    cout << " ------------------------------------------- " << endl;
    cout << " a) Add Player Data " << endl;
    cout << " b) Delete a Player " << endl;
    cout << " c) Display Name of Highest Stats " << endl;
    cout << " d) Display Name of Lowest Stats " << endl;
    cout << " e) List Name(s) of Player(s) with Triple Double " << endl;
    cout << " f) Display List of Points (in descending order)" << endl;
    cout << " q) Quit program and exit " << endl; 
    cout << " Enter your choice (a-f or q) : ";
    cin >> choice;

    switch (choice)
    {
    // a) Get players info from user to add player data
    case 'a': cout << endl << "Add Player Data: " << endl << endl;
    cout << "Enter player name: " << endl;
    cin >> playerName;
    cout << "Enter " << playerName << "'s team name " << endl;
    cin >> teamName;
    cout << "Enter " << playerName << "'s points " << endl;
    cin >> numPoints;
    cout << "Enter " << playerName << "'s assists " << endl;
    cin >> numAssists;
    cout << "Enter " << playerName << "'s rebounds " << endl;
    cin >> numRebounds;
    // now when user inputs info, we insert them to their respective tree
    pointsBST.TREE_INSERT(playerName, teamName, numPoints);
    assistBST.TREE_INSERT(playerName, teamName, numAssists);
    reboundsBST.TREE_INSERT(playerName, teamName, numRebounds);;
    break;

    // b) Gets player inputted by user and deletes him from all three BST's (pts, ast, & reb)
    case 'b': cout << endl << "Delete a Player: " << endl << endl;
    cout << "Enter the player's name that you would like to remove " << endl;
    cin >> playerName;
    cout << "Enter exactly this player's number of points " << endl;
    cin >> numPoints;
    cout << "Enter exactly this player's number of asissts " << endl;
    cin >> numAssists;
    cout << "Enter exactly this player's number of rebounds " << endl;
    cin >> numRebounds;
    pointsBST.DELETEPLAYER(pointsBST.root, numPoints);
    assistBST.DELETEPLAYER(assistBST.root, numAssists);
    reboundsBST.DELETEPLAYER(reboundsBST.root, numRebounds);
    cout << "The player: " << playerName << " has now been removed from all three BST's " << endl;
    break;

    // c) Displays the players with the highest stats for the three respective stats
    case 'c': cout << endl << "Displaying Name of Players with the Highest Statistics: " << endl;
    // we call the functions which finds the max for each stat and display that players info
    pointsBST.DISPLAYMAXPTS(pointsBST.root);
    assistBST.DISPLAYMAXASTS(assistBST.root);
    reboundsBST.DISPLAYMAXREBS(reboundsBST.root);
    break;

    case 'd': cout << endl << "Displaying Name of Players with the Lowest Statistics: " << endl;
    // call the functions which finds the min of each BST and displays that players info
    pointsBST.DISPLAYLOWPTS(pointsBST.root);
    assistBST.DISPLAYLOWASTS(assistBST.root);
    reboundsBST.DISPLAYLOWREBS(reboundsBST.root);
    break;

    case 'e': cout << endl << "Listing Players who Average a Triple Double " << endl;

    break;

    case 'f': cout << endl << "Displaying Players Point Statistics (in descending order) " << endl;
    pointsBST.DESCENDING_WALK(pointsBST.root); // simply calling DECENDING_WALK which lists players in descending order by thier pts
    break;

    // q) Exit program
    case 'q': 
    cout << " Quitting/Exiting program ... " << endl; 
    system("pause"); // simply puts pause to the program and quits
    return 0;
    break;

    default:
    cout << "Invalid choice, choose a character between a and f or q to quit!";
    }
    }
}