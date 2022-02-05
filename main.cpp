#include <iostream>

using namespace std;

struct nodeBST {
    nodeBST * left;
    nodeBST * right;
    nodeBST * father;
    int key;
};

void deleteBST ( nodeBST * T ) {
    if ( T ) {
        deleteBST(T -> left );
        deleteBST(T -> right );
        delete T;
    }
}

int hBST ( nodeBST * T ) {
    if ( T == nullptr ) return 0;
    else {
        int hLeft = hBST( T -> left );
        int hRight = hBST( T -> right );

        if ( hLeft > hRight ) return hLeft + 1;
        else return hRight + 1;
    }
}

void insertBST ( nodeBST * & T, int key ) {
    nodeBST * newNode, * prevNode;
    newNode = new nodeBST;
    newNode -> left = nullptr;
    newNode -> right = nullptr;
    newNode -> key = key;

    prevNode = T;

    if( !prevNode ) T = newNode;
    else {
        while ( true ) {
            if ( key < prevNode -> key ) {
                if ( !prevNode -> left ) {
                    prevNode -> left = newNode;
                    break;
                } else prevNode = prevNode -> left;
            } else {
                if ( !prevNode -> right ) {
                    prevNode -> right = newNode;
                    break;
                } else prevNode = prevNode -> right;
            }
        }
    }
    newNode -> father = prevNode;
}

nodeBST * nextBST ( nodeBST * L ) {
    nodeBST * R;
    if ( L ) {
        if ( L -> right ) {
            L = L -> right;
            if ( L ) while ( L -> left ) L = L -> left;
            return L;
        } else {
            R = L -> father;
            while (R && (L == R -> right ) ) {
                L = R;
                R = R -> father;
            }
            return R;
        }
    } else return L;
}

void removeBST ( nodeBST * & T, int key ){
    nodeBST * nodeWithKey, * tmpT1, * tmpT2;

    nodeWithKey = T;
    while (nodeWithKey && nodeWithKey -> key != key ){
        if (key < nodeWithKey -> key ) nodeWithKey = nodeWithKey -> left;
        else nodeWithKey = nodeWithKey -> right;
    }

    if ( nodeWithKey ) {
        if ( !nodeWithKey -> left || !nodeWithKey -> right ) tmpT1 = nodeWithKey;
        else tmpT1 = nextBST( nodeWithKey );

        if ( tmpT1 -> left ) tmpT2 = tmpT1 -> left;
        else tmpT2 = tmpT1 -> right;

        if ( tmpT2 ) tmpT2 -> father = tmpT1 -> father;

        if( !tmpT1 -> father ) T = tmpT2;
        else if( tmpT1 == tmpT1 -> father -> left ) tmpT1 -> father -> left = tmpT2;
        else tmpT1 -> father -> right = tmpT2;

        if ( tmpT1 != nodeWithKey ) nodeWithKey -> key = tmpT1 -> key;
        delete tmpT1;
    } else cout << endl << "No vertex with specified key." << endl;
}

void preorderBST ( nodeBST * T ) {
    if ( T ) {
        cout << T -> key << " ";
        preorderBST( T -> left );
        preorderBST( T -> right );
    }
}

void inorderBST ( nodeBST * T ) {
    if ( T ) {
        inorderBST ( T -> left );
        cout << T -> key << " ";
        inorderBST ( T -> right );
    }
}

void postorderBST ( nodeBST * T ) {
    if ( T ) {
        postorderBST(T -> left );
        postorderBST(T -> right );
        cout << T -> key << " ";
    }
}

void levelOrderBST_printLevel ( nodeBST * T, int level ) {
    if ( T == nullptr ) return;
    if ( level == 1 ) cout << T -> key << " ";
    else if ( level > 1 ) {
        levelOrderBST_printLevel( T -> left, level - 1 );
        levelOrderBST_printLevel( T -> right, level - 1 );
    }
}

void levelOrderBST ( nodeBST * T ) {
    int h = hBST( T );
    for ( int i = 1; i <= h; i++ )
        levelOrderBST_printLevel( T, i );
}

void variantLevelOrderBST_printLevel ( nodeBST * T, int level, int prev, string direction ) {
    if ( T == nullptr ) return;
    if ( level == 1 ) {
        if ( prev == 0 ) cout << "(" << T -> key << "){ root } ";
        else cout << "(" << T -> key << "){ (" << prev << ") - " << direction << " }   ";
    } else {
        variantLevelOrderBST_printLevel( T -> left, level - 1, T->key, "left" );
        variantLevelOrderBST_printLevel( T -> right, level - 1, T->key, "right" );
    }
}

void variantLevelOrderBST ( nodeBST * T ) {
    int h = hBST( T );
    for ( int i = 0; i <= h; i++ ) {
        variantLevelOrderBST_printLevel( T, i, 0, "" );
        cout << endl;
    }
}

void printBST ( nodeBST * T, int op ) {
    switch ( op ) {
        case 1: inorderBST( T ); break;
        case 2: preorderBST( T ); break;
        case 3: postorderBST( T ); break;
        case 4: levelOrderBST( T ); break;
        case 5: variantLevelOrderBST( T ); break;
        default: break;
    }
}

int countLevBST_numberAtLevel ( nodeBST * T, int actual, int desired ){
    if ( T == nullptr ) return 0;
    if ( actual == desired ) return 1;
    return countLevBST_numberAtLevel( T -> left, actual + 1, desired ) +
           countLevBST_numberAtLevel( T -> right, actual + 1, desired );
}

int countLevBST ( nodeBST * T, int lev ){
    static int actual = 0;
    if ( T == nullptr ) return 0;
    if ( actual == lev ) return 1;
    return countLevBST_numberAtLevel( T -> left, actual + 1, lev ) +
           countLevBST_numberAtLevel( T -> right, actual + 1, lev );
}

int isCompleteBST_numberOfNodes ( nodeBST * T ) {
    if ( T == nullptr ) return 0;
    return ( 1 + isCompleteBST_numberOfNodes(T -> left) + isCompleteBST_numberOfNodes(T -> right) );
}

bool isCompleteBST ( nodeBST * root, int index, int number_nodes )
{
    if ( number_nodes == -1 ) number_nodes = isCompleteBST_numberOfNodes( root );
    if ( root == nullptr ) return true;
    if ( index >= number_nodes ) return false;

    return ( isCompleteBST( root -> left, 2 * index + 1, number_nodes ) &&
             isCompleteBST( root -> right, 2 * index + 2, number_nodes ) );
}

void tableBST ( nodeBST * T, int keys[] ) {
    if (isCompleteBST(T, 0, -1) ) {
        static int pos = 0;
        if ( T ) {
            tableBST( T -> left, keys );
            keys[ pos++ ] = T -> key;
            tableBST( T -> right, keys );
        }
    } else cout << "Tree is not complete. | ";
}

void inOrderTableBST ( nodeBST * T, int keys[] ) {
    static int pos = 0;
    if ( T ) {
        inOrderTableBST( T -> left, keys );
        keys[ pos++ ] = T -> key;
        inOrderTableBST( T -> right, keys );
    }
}

void preOrderTableBST ( nodeBST * T, int keys[] ) {
    static int pos = 0;
    if ( T ) {
        keys[ pos++ ] = T -> key;
        preOrderTableBST( T -> left, keys );
        preOrderTableBST( T -> right, keys );
    }
}

nodeBST * inPreBST ( int in[], int pre[], int size ) {
    nodeBST * root = nullptr;
    int i;

    for ( i = 0; i < size; i++ ) insertBST( root, in[i] );
    for ( i = 0; i < size; i++ ) insertBST( root, pre[i] );

    return root;
}

int main( )
{
    srand( time(nullptr) );
    int i, j, n;
    nodeBST * root = nullptr;

    //Complete tree
    insertBST ( root, 20 );
    insertBST ( root, 10 );
    insertBST ( root, 30 );
    insertBST ( root, 8 );
    insertBST ( root, 12 );
    insertBST ( root, 28 );
    insertBST ( root, 32 );

    //After removal, the tree is still complete
    removeBST( root, 30 );

    cout << "(op:1 - op:5):" << endl;
    for ( i = 1; i <= 5; i++ ) {
        printBST( root, i );
        cout << endl;
    }

    cout << "Height: " << hBST( root );
    cout << endl;

    int level = 2;
    cout << "Number of vertices per level " << level << ": " << countLevBST( root, level );
    cout << endl;

    int *array = new int[n];
    tableBST( root, array );
    cout << "Board form (if the tree is complete): ";
    for ( i = 0; i < isCompleteBST_numberOfNodes( root ); i++ )
        cout << array[i] << ' ';
    cout << endl;
    delete [] array;

    n = isCompleteBST_numberOfNodes( root );
    int *in = new int[n];
    int *pre = new int[n];
    inOrderTableBST( root, in );
    preOrderTableBST( root, pre );
    for ( i = 0; i < isCompleteBST_numberOfNodes( root ); i++ )
        cout << in[i] << ' ';
    cout << endl;
    for ( i = 0; i < isCompleteBST_numberOfNodes( root ); i++ )
        cout << pre[i] << ' ';
    cout << endl;

    deleteBST( root );
    root = nullptr;

    root = inPreBST( in, pre, n );
    //the structure shows that on each level there are 2 identical nodes (except for level 0 and 1,
    //which are also identical)
    printBST( root, 5 );
    delete [] in;
    delete [] pre;


    deleteBST( root );
    root = nullptr;

    cout << endl << "Enter n:";
    cin >> n;

    for( i = 0; i < n; i++ ) {
        int value = rand() % 1000 + 1;
        insertBST ( root, value );

        cout << "(op:1 - op:5):" << endl;
        for ( j = 1; j <= 5; j++ ) {
            printBST( root, j );
            cout << endl;
        }

    }

    return 0;
}