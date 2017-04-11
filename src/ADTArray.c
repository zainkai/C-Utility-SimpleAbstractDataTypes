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
    if(Capacity == 0){
        return NULL;
    }

    int i;

    ADTArray* obj = malloc(sizeof(ADTArray));
    obj->Data = malloc(Capacity * sizeof(void*));

    for(i = 0;i < Capacity; i++){
        obj->Data[i] = NULL;
    }

    obj->MaxCapacity = Capacity;
    obj->CurrentSize = 0;

    return obj;
}

void _ADTArrayFreeData(void** Data, int MinIdx,int MaxIdx){
    int i;

    for(i = MinIdx; i < MaxIdx; i++){
        if(Data[i] != NULL){
            free(Data[i]);
        }
    }
}

void ADTArrayFree(ADTArray* obj)
{
    if(obj == NULL){
        return;
    }  

    _ADTArrayFreeData(obj->Data,0,obj->MaxCapacity + 1); 

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
    if(obj == NULL || idx < -1){
        return NULL;
    }
    else if(obj->MaxCapacity < idx){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->CurrentSize -1;
    }

    obj->CurrentSize++;
    
    return obj->Data[idx] = item;
}

ADTArray* ADTArrayClearItem(ADTArray* obj,int idx){
    if(obj == NULL || idx < -1){
        return NULL;
    }
    else if(obj->MaxCapacity < idx || (obj->Data[idx] == NULL)){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->CurrentSize -1;
    }

    free(obj->Data[idx]);
    obj->Data[idx] = NULL;

    return obj;
}

ADTArray* ADTArrayResize(ADTArray* obj, int NewCapacity)
{
    if(obj == NULL || NewCapacity < 0){
        return NULL;
    }

    int i;
    void** NewData = malloc(NewCapacity * sizeof(void*));
    
    for(i = 0; i < NewCapacity;i++){
        //swapping pointers to items.
        NewData[i] = obj->Data[i];
    }

    //check if offset is negative
    if((obj->MaxCapacity - NewCapacity) < 0){
        _ADTArrayFreeData(obj->Data,NewCapacity,obj->MaxCapacity + 1);
    }

    free(obj->Data);
    obj->Data = NewData;

    return obj;
}

void* ADTArrayInsert(ADTArray* obj, int idx, void* item)
{
    if(obj == NULL || idx < -1){
        return NULL;
    }
    else if(obj->CurrentSize == obj->MaxCapacity){
        return NULL;
    }
    else if(idx == -1){
        idx = obj->CurrentSize -1;
    }

    int i;

    for(i = obj->CurrentSize; i > idx;i--){
        obj->Data[i] = obj->Data[i -1]; 
    }

    obj->CurrentSize++;

    return obj->Data[idx] = item;
}

void ADTArrayRemove(ADTArray* obj, int idx)
{
    if(obj == NULL || idx < -1){
        return;
    }
    else if(idx == -1){
        idx = obj->CurrentSize -1;
    }

    int i;

    free(obj->Data[idx]);

    for(i = idx; i < obj->CurrentSize - 1; i++){
        obj->Data[i] = obj->Data[i+1];
    }

    obj->CurrentSize--;
}


int main()
{
    ADTArray* arr = ADTArrayCreate(100);
    ADTArrayFree(arr);

    return 0;
}