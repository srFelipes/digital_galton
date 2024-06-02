int all_0s_calls;
void test_utils_init(){
    all_0s_calls = 0;
}

void all_0s(char output_array[], unsigned int n_of_bits){
    int n = (n_of_bits>>3)+1;
    for (int i = 0; i<n; i++){
        output_array[i] = 0;
    }
    all_0s_calls++;
}