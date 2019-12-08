
#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

//iterative funciton that recieves the bst_root and the insInt
//bst_insert searches the bst for insInt and if not found, 
//    inserts the insInt in the appropriate postition, 
//    otherwise it does nothing 
void bst_insert(btNode*& bst_root, int insInt)
{ 
   btNode *newNode = new btNode; 
   newNode->data = insInt;
   newNode->left = newNode->right = 0; 
   bool found = false; 
   bool insert = false;

   btNode* cursor = bst_root;
   if(cursor == 0)  { //bst is empty
      bst_root = newNode; 
      insert = true; 
   } 
   else { //bst is not empty 
      while (!found & !insert)
      { //while the insInt is not found or has not been inserted 
         if (insInt == cursor->data)
            found = true; 
         if (insInt > cursor->data){
            if (cursor-> right == 0){
               cursor->right = newNode; 
               insert = true; 
            }
            else
               cursor = cursor->right;
         }
         if (insInt < cursor->data){
            if (cursor->left == 0){
               cursor->left = newNode; 
               insert = true; 
            }
            else
               cursor = cursor->left; 
         }
      }
   }
}

//recursive function that recieves a smaller and smaller bst 
//    with the data field of the orgninal bst_root it will replace
//bst_remove_max removes the maximum value of the LST and 
//    sets the parent node data field to such
void bst_remove_max(btNode*& bst_root, int& data) 
{
   btNode* temp = bst_root; 
   if(bst_root->right == 0) 
   { //no RST; base case 
      data = bst_root->data;
      temp = bst_root;
      bst_root = bst_root->left; 
      delete temp;
      return; 
   }
   else //has RST
      bst_remove_max(bst_root->right, data); 
}

//recursive function that receives a smaller and smaller bst and 
//    the remInt it is searching for
//bst_remove returns true and removes the remInt from the bst 
//    if the value is in the list, otherwise bst_remove returns 
//    false and keeps the list as is 
bool bst_remove(btNode*& bst_root, int remInt){
   btNode* temp;  
   if (bst_root != 0)
   { //base case implied
      if (remInt > bst_root->data)
         return bst_remove(bst_root->right, remInt);
      if(remInt < bst_root->data)
         return bst_remove(bst_root->left, remInt);
      if(bst_root->data == remInt){
         if(bst_root->left == 0 && bst_root->right == 0)  
         { //empty
            temp = bst_root; 
            bst_root = 0;  
            delete temp; 
         }
         else if (bst_root->left == 0) 
         { //only RST
            temp = bst_root; 
            bst_root = bst_root->right; 
            delete temp; 
         } 
         else if(bst_root->right == 0) 
         { //only LST
            temp = bst_root; 
            bst_root = bst_root->left; 
            delete temp; 
         }
         else //root has LST and RST
            bst_remove_max(bst_root->left, bst_root->data);
         return true; 
      } 
   }
   return false;
}
