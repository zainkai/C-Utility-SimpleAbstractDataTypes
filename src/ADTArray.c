#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int CurrentSize;
    int MaxCapacity;
    void** Data;
} ADTArray;

ADTArray* ADTArrayCreate(int Capacity)
{
    int i;

    if(Capacity == 0){
        return NULL;
    }

    ADTArray* obj = malloc(sizeof(ADTArray));
    obj->Data = malloc(Capacity * sizeof(void*));

    for(i = 0;i < Capacity; i++){
        obj->Data[i] = NULL;
    }

    obj->MaxCapacity = Capacity;
    obj->CurrentSize = 0;

    return obj;
}

void ADTArrayFree(ADTArray* obj)
{
    int i;

    if(obj == NULL){
        return;
    }

    for(i = 0; i < obj->MaxCapacity + 1; i++){
        if(obj->Data[i] != NULL){
            free(obj->Data[i]);
        }
    }    

    free(obj->Data);
    free(obj);
}

int ADTArraySize(ADTArray* obj){
    if(obj == NULL){
        return -1;
    }
    
    return obj->CurrentSize;
}

void* ADTArrayGet(ADTArray* obj, int idx)
{
    if(obj == NULL){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->CurrentSize -1;
    }

    return obj->Data[idx];
}

void* ADTArraySet(ADTArray* obj,int idx, void* item)
{
    if(obj == NULL){
        return NULL;
    }
    else if(obj->MaxCapacity < idx || idx < -1){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->CurrentSize -1;
    }

    return obj->Data[idx] = item;
}

ADTArray* ADTArrayResize(ADTArray* obj, int NewCapacity)
{
    int i,offset;

    if(obj == NULL){
        return NULL;
    }
    else if(NewCapacity < 0){
        return NULL;
    }

    void** NewData = malloc(NewCapacity * sizeof(void*));
    

    for(i = 0; i < NewCapacity;i++){
        NewData[i] = obj->Data[i];
    }

    offset = obj->MaxCapacity - NewCapacity;
    if(offset < 0){
        for(i = NewCapacity;i < obj->MaxCapacity + 1;i++){
            if(obj->Data[i] != NULL){
                free(obj->Data[i]);
            }
        }
    }

    free(obj->Data);
    obj->Data = NewData;

    return obj;
}


int main()
{
    ADTArray* arr = ADTArrayCreate(100);
    ADTArrayFree(arr);

    return 0;
}