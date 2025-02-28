#ifndef DISJOINTSET_H
#define DISJOINTSET_H

    #include <vector>
    #include <iostream>

    #define uint unsigned int

    using namespace std;

    template <typename T>
    class DisjointSet
    {
        // Disjoint Set Node
        struct Node
        {

            // value of node
            T value;

            // node's parent
            // default to this
            Node * parent = nullptr;

            // node's rank
            // how many connections it is from the parent node
            uint rank;
            
            Node(T value) : value(value), parent(this), rank(1)
            {

            }

            ~Node()
            {
            }
        
            Node & operator =(const Node & other)
            {
                value = other.value;
                return *this;
            }

            T operator -(const Node & other) const
            {
                return this->value - other.value;
            }

            T operator +(const Node & other) const
            {
                return this->value + other.value;
            }

        };

        // list of subsets in disjoint set
        vector<Node> sets;
        uint n_sets;

        Node * GetSubsetFromIndex(uint index)
        {
            // check bounds
            return &sets[index];
        }
        
        bool SubsetOutOfBounds(uint subset1, uint subset2)
        {
            if (subset1 == subset2 || subset1 >= sets.size() || subset1 < 0 
                || subset2 >= sets.size() || subset2 < 0)
            {
                return true;
            }
            return false;
        }
        
        // find the root of the given subset
        Node * FindRoot(DisjointSet<T>::Node * subset)
        {
        
            // move up subset parents until finding loop
            while(subset->parent != subset)
            {
                subset = subset->parent;
            }
        
            return subset;
        
        }

    public:

        DisjointSet()
        {

        }
        
        ~DisjointSet()
        {
            uint s = sets.size();
            for(uint i = 0; i < s; i++)
            {
                delete &sets[i];
            }
        }

        DisjointSet( const DisjointSet & other)
        {
            uint s = other.sets.size();
            for(uint i = 0; i < s; i++)
            {
                sets.push_back(Node(other.sets[i]).value);
            }
        }
        
        // remove all subsets
        void clear()
        {
            sets.clear();
        }
        
        // create new disjoint set with n nodes
        void NewSubset(uint n)
        {   

            clear();

            for(uint i = 0; i < n; i++)
            {
                Node * newNode = new Node(15);
                sets.push_back(*newNode);
            }
        
            n_sets = n;
        
        }
        
        // get number of subsets in disjoint set
        uint NumSets() const
        {
            return n_sets;
        }

        // merge two sets
        bool Union(uint subset1, uint subset2)
        {

            if(SubsetOutOfBounds(subset1, subset2))
            {
                return false;
            }

            Node * subsetNode1 = GetSubsetFromIndex(subset1);
            Node * subsetNode2 = GetSubsetFromIndex(subset2);

            Node * root1 = FindRoot(subsetNode1);
            Node * root2 = FindRoot(subsetNode2);

            if(root1 == root2)
            {
                return false;
            }

            // if root1 outranks root2, connect root1 to root2's parent
            if((root1->rank) > (root2->rank))
            {
                root2->parent = root1;
            }
            else if((root1->rank) < (root2->rank))
            {
                root1->parent = root2;
            }
            else
            {
                root2->parent = root1;
                root1->rank++;
            }

            n_sets--;

            return true;

        }

        bool SameSet(uint subset1, uint subset2)
        {

            if(SubsetOutOfBounds(subset1, subset2))
            {
                return false;
            }

            DisjointSet<T>::Node * a = GetSubsetFromIndex(subset1);
            DisjointSet<T>::Node * b = GetSubsetFromIndex(subset2);

            a = FindRoot(a);
            b = FindRoot(b);

            return a == b;

        }

        // [] get operator
        uint & operator [] (uint index)
        {
            if(index > sets.size())
            {
                throw std::out_of_range("Set index out of range");
            }
            return sets[index].value;
        }

    };

#endif