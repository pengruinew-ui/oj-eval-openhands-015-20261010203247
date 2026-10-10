#include <bits/stdc++.h>
using namespace std;
static const int BUCKET_COUNT = 19;
static int bucket_id(const string& key){return (int)(hash<string>{}(key)%BUCKET_COUNT);} 
int main(){cout<<bucket_id("key1")<<"\n";}
