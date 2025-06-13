#define MOD 100000
#include <stdlib.h>

typedef struct HNode{
    int key;
    int val;
    struct HNode* next;
} HNode;

HNode* newHNode(int key, int val, HNode* next){
    HNode* obj = (HNode*)malloc(sizeof(HNode));
    obj->key = key;
    obj->val = val;
    obj->next = next;
    return obj;
}

typedef struct {
    HNode dummy[MOD];
} MyHashMap;


MyHashMap* myHashMapCreate() {
    MyHashMap* obj  = (MyHashMap*)calloc(sizeof(MyHashMap), 1);
    return obj;
}

int hashFunc(int key){
    return key % MOD;
}

int myHashMapGet(MyHashMap* obj, int key) {
    int _key = hashFunc(key);
    for(HNode* p = obj->dummy[_key].next; p; p = p->next){
        if(p->key == key) return p->val;
    }
    return -1;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    int _key = hashFunc(key);
    for(HNode* p = obj->dummy[_key].next; p; p = p->next){
        if(p->key == key) {
            p->val = value;
            return;
        }
    }
    HNode* hnode = newHNode(key, value, obj->dummy[_key].next);
    obj->dummy[_key].next = hnode;
}

void myHashMapRemove(MyHashMap* obj, int key) {
    int _key = hashFunc(key);
    HNode* prev = &obj->dummy[_key], *p = NULL;
    for(p = obj->dummy[_key].next; p; p = p->next){
        if(p->key == key){
            prev->next = p->next;
            free(p);
            break;
        }
    }
}

void myHashMapFree(MyHashMap* obj) {
    for(int i = 0; i < MOD; i++){
        for(HNode* p = obj->dummy[i].next; p;){
            HNode* next = p->next;
            free(p);
            p = next;
        }
    }
    free(obj);
}