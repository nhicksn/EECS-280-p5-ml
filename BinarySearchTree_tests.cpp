// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


TEST(test_empty) {
    BinarySearchTree<int> Tree;
    assert(Tree.empty());
    Tree.insert(3);
    assert(!Tree.empty());
}

//size
TEST(test_size_basic){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    ASSERT_EQUAL(Tree.size(), 1);
    Tree.insert(309);
    ASSERT_EQUAL(Tree.size(), 2);
}

//height
TEST(test_height_basic){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    Tree.insert(4);
    Tree.insert(2);
    ASSERT_EQUAL(Tree.height(), 2);
}

TEST(test_height_stick){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    Tree.insert(4);
    Tree.insert(5);
    Tree.insert(6);
    ASSERT_EQUAL(Tree.height(), 4);
}

TEST(test_height_one){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    ASSERT_EQUAL(Tree.height(), 1);
}

//copy nodes

//destroy nodes

//find

//min element
TEST(test_min_element_basic){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    Tree.insert(4);
    Tree.insert(2);
    ASSERT_EQUAL(*Tree.min_element(), 2);
}

TEST(test_min_element_negative){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    Tree.insert(4);
    Tree.insert(2);
    Tree.insert(7);
    Tree.insert(-1);
    Tree.insert(1);
    ASSERT_EQUAL(*Tree.min_element(), -1);
}

TEST(test_min_element_node_is_min){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    Tree.insert(7);
    Tree.insert(5);
    Tree.insert(6);
    ASSERT_EQUAL(*Tree.min_element(), 3);
}

//max element
TEST(test_max_element_basic){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    Tree.insert(4);
    Tree.insert(2);
    ASSERT_EQUAL(*Tree.max_element(), 4);
}

TEST(test_max_element_large_tree){
    BinarySearchTree<int> Tree;
    Tree.insert(3);
    Tree.insert(7);
    Tree.insert(2);
    Tree.insert(6);
    Tree.insert(15);
    Tree.insert(-1);
    ASSERT_EQUAL(*Tree.max_element(), 15);
}

TEST(test_max_element_node_is_max){
    BinarySearchTree<int> Tree;
    Tree.insert(13);
    Tree.insert(7);
    Tree.insert(5);
    Tree.insert(6);
    ASSERT_EQUAL(*Tree.max_element(), 13);
}

//check sorting invariant

//traverse in order

//traverse preorder

//min greater than

//

TEST_MAIN()
