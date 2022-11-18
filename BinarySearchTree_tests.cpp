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
TEST(test_copy_constructor) {
    BinarySearchTree<int> tree1;
    tree1.insert(5);
    tree1.insert(3);
    BinarySearchTree<int>::Iterator iter1 = tree1.begin();
    ASSERT_EQUAL(*iter1, 3);
    ++iter1;
    ASSERT_EQUAL(*iter1, 5);
    ASSERT_EQUAL(tree1.size(), 2);
    BinarySearchTree<int> tree2 = tree1;
    BinarySearchTree<int>::Iterator iter2 = tree2.begin();
    ASSERT_EQUAL(*iter2, 3);
    ++iter2;
    ASSERT_EQUAL(*iter2, 5);
    ASSERT_EQUAL(tree2.size(), 2);
}

//destroy nodes
TEST(test_assignment_operator) {
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2;
    tree1.insert(0);
    tree1.insert(4);
    tree1.insert(-4);
    tree2.insert(-10);
    tree2.insert(-12);
    tree2.insert(-14);
    tree2.insert(-8);
    ASSERT_EQUAL(tree2.size(), 4);
    tree2 = tree1;
    ASSERT_EQUAL(tree2.size(), 3);
    BinarySearchTree<int>::Iterator iter = tree2.begin();
    ASSERT_EQUAL(*iter, -4);
    ++iter;
    ASSERT_EQUAL(*iter, 0);
    ++iter;
    ASSERT_EQUAL(*iter, 4);
    ++iter;
    ASSERT_EQUAL(iter, tree2.end());
}

//find
TEST(test_find_basic) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(0);
    tree.insert(-4);
    BinarySearchTree<int>::Iterator iter = tree.find(-4);
    ASSERT_EQUAL(iter, tree.begin());
    ++iter;
    BinarySearchTree<int>::Iterator iter2 = tree.find(0);
    ASSERT_EQUAL(iter, iter2);
    iter2 = tree.find(4);
    ++iter;
    ASSERT_EQUAL(iter, iter2);
    iter2 = tree.find(3);
    ASSERT_EQUAL(tree.end(), iter2);
}

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
TEST(check_sorting_invariant) {
    BinarySearchTree<int> tree;
    tree.insert(0);
    tree.insert(-2);
    tree.insert(2);
    assert(tree.check_sorting_invariant());
    BinarySearchTree<int>::Iterator iter = tree.begin();
    *iter = 2;
    assert(!tree.check_sorting_invariant());
}

//traverse in order
TEST(test_traverse_in_order) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    std::ostringstream output;
    tree.traverse_inorder(output);
    std::ostringstream correct;
    correct << "2 4 6 ";
    ASSERT_EQUAL(output.str(), correct.str());
}

//traverse preorder
TEST(test_traverse_preorder) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    std::ostringstream output;
    tree.traverse_preorder(output);
    std::ostringstream correct;
    correct << "4 2 6 ";
    ASSERT_EQUAL(output.str(), correct.str());
}

//min greater than
TEST(min_greater_than) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    BinarySearchTree<int>::Iterator iter = tree.min_greater_than(2);
    ASSERT_EQUAL(*iter, 4);
    iter = tree.min_greater_than(6);
    ASSERT_EQUAL(iter, tree.end());
}

//

TEST_MAIN()
