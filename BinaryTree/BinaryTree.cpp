#include <iostream>
#include <random>

struct Node
{
    Node* parent{ nullptr };
    Node* left{nullptr};
    Node* right{nullptr};

    int number{ 0 };

    Node(int val)
    {
        number = val;
    }
};

class BinaryTree
{
private:
    Node* root{ nullptr };
    void freeMemory(Node* root);
    
public:
    
    Node* findNode(int num) const;
    Node* min(Node* startNode) const;
    Node* max(Node* startNode) const;

    void deleteNode(int num);
    void addNode(int num);
    void searchNode(int searchNum) const;

    const Node* getRoot() const
    {
        return root;
    }

    void printMinMax() 
    {
        std::cout << "min node " << min(root)->number << "\n";
        std::cout << "max node " << max(root)->number << "\n";
    };

    //Constructor
    BinaryTree(int rootNum)
    {
        root = new Node(rootNum);
    }

    //Destructor
    ~BinaryTree()
    {
        freeMemory(root);
        std::cout << "Deallocation complete!" << "\n";
    }
};

void BinaryTree::searchNode(int searchNum) const
{
    Node* traverser = root;

    int steps{};

    do
    {
        std::cout << "looking for Node..." << searchNum << " Currently on Node: " << traverser->number << "\n";

        if (searchNum < traverser->number)
        {
            //traverse left
            std::cout << "Traversing Left" << "\n";
            traverser = traverser->left;
            ++steps;
        }
        else if (searchNum > traverser->number)
        {
            //traverse right
            std::cout << "Traversing right" << "\n";
            traverser = traverser->right;
            ++steps;
        }

        if (traverser == nullptr) break;

    } while (searchNum != traverser->number);

    if (traverser != nullptr && searchNum == traverser->number)
    {
        std::cout << "Node: " << searchNum << " found in " << steps << " steps!" << "\n";
        return;
    }
    else
    {
        std::cout << "Node could not be found!" << "\n";
    }
}

void BinaryTree::deleteNode(int num)
{
    Node* nodeToDelete = findNode(num); 

    if (nodeToDelete == nullptr) return;

    if ((nodeToDelete->right != nullptr && nodeToDelete->left != nullptr))
    {
        //Node has two children
        Node* minNode = min(nodeToDelete->right); // Get the tinniest node on the right side of the tree/node parameter 

        if (minNode == nullptr)
        {
            minNode = nodeToDelete->right;
        }

        nodeToDelete->number = minNode->number; // Switch the data that u want removed with the minNode data
        
        //Check if minNode has any children
        if (minNode->right != nullptr)
        {
            //Switch the parent pointer of minNode child to point towards parent of minNode
            minNode->right->parent = minNode->parent;

            //Switch pointer of minNode parent too point towards child of minNode
            minNode->parent->right = minNode->right;
        }

        std::cout << "This thing has two children!!!" << "\n";

        minNode->parent->left = nullptr;

        delete minNode;
    }
    else if ((nodeToDelete->left && !nodeToDelete->right) || (!nodeToDelete->left && nodeToDelete->right))
    {
        //node only has only one child
        std::cout << "This thing has only one child..." << "\n";
       
        if (nodeToDelete->number < nodeToDelete->parent->number)
        {
            if (nodeToDelete->left != nullptr)
            {
                nodeToDelete->left->parent = nodeToDelete->parent;
                nodeToDelete->parent->left = nodeToDelete->left;
            }
            else if(nodeToDelete->right != nullptr)
            {
                nodeToDelete->right->parent = nodeToDelete->parent;
                nodeToDelete->parent->left = nodeToDelete->right;
            }
        }
        else
        {
            if (nodeToDelete->left != nullptr)
            {
                nodeToDelete->left->parent = nodeToDelete->parent;
                nodeToDelete->parent->right = nodeToDelete->left;
            }
            else if (nodeToDelete->right != nullptr)
            {
                nodeToDelete->right->parent = nodeToDelete->parent;
                nodeToDelete->parent->right = nodeToDelete->right;
            }
        }

        delete nodeToDelete;
    }
    else
    {
        //node has no children
        std::cout << "This thing has NO CHILDREN..." << "\n";
        if (nodeToDelete->number < nodeToDelete->parent->number)
            nodeToDelete->parent->left = nullptr;
        else if (nodeToDelete->number > nodeToDelete->parent->number)
            nodeToDelete->parent->right = nullptr;
        
        delete nodeToDelete;
    }

    std::cout << "Deleted Node: " << num << "\n";
}

void BinaryTree::freeMemory(Node* root)
{
    if (root == nullptr) return;

    freeMemory(root->left);
    freeMemory(root->right);

    delete root;
}

Node* BinaryTree::findNode(int num) const
{
    Node* traverser = root;
    do
    {
        if (num < traverser->number)
        {
            //traverse left
            traverser = traverser->left;
        }
        else if (num > traverser->number)
        {
            //traverse right
            traverser = traverser->right;
        }
        if (traverser == nullptr) return nullptr;

    } while (num != traverser->number);

    if (traverser != nullptr && num == traverser->number)
    {
        return traverser;
    }
    else
    {
        std::cout << "Node " << num << " could not be added!" << "\n";
        return nullptr;
    }

    return nullptr;
}

void BinaryTree::addNode(int num)
{
    if (num < root->number || num > root->number)
    {
        Node* traverser = root;

        do
        {
            if (num < traverser->number)
            {
                if (traverser->left == nullptr)
                {
                    Node* node = new Node(num); //create new node at left position 
                    node->parent = traverser;
                    traverser->left = node;
                    return;
                }
                traverser = traverser->left;
            }
            else if (num > traverser->number)
            {
                if (traverser->right == nullptr)
                {
                    Node* node = new Node(num);  //create new node at right position 
                    node->parent = traverser;
                    traverser->right = node;
                    return;
                }
                traverser = traverser->right; // This is underneath, because if traverser->right is nullptr, we move to nullptr and then we make a node that is not connected
            }
            if (traverser->number == num)
            {
                std::cout << "Number " << num << " already exists in the binary tree!" << "\n";
                return;
            }
        } while (traverser->number != num);
    }
    else
    {
        std::cout << "Number is already root! " << "\n";
        return;
    }
}

Node* BinaryTree::max(Node* startNode) const
{
    Node* maxNode = startNode;
    Node* traverser = startNode;

    while (traverser != nullptr)
    {
        maxNode = traverser;
        traverser = traverser->right;
    }

    return maxNode;
}

Node* BinaryTree::min(Node* startNode) const
{
    Node* minNode = startNode;
    Node* traverser = startNode;

    while (traverser != nullptr)
    {
        minNode = traverser;
        traverser = traverser->left;
    }

    return minNode;
}


