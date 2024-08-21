def generate_c_file(unroll_factor):
    code = f"""
#include <stdio.h>
#include <time.h>

#define ARRAY_SIZE 1000000

int main() {{
    int array[ARRAY_SIZE];
    int sum = 0;

    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    for (int i = 0; i < ARRAY_SIZE; i += {unroll_factor}) {{
        // Loop operation
        """
    
    for i in range(unroll_factor):
        code += f"sum += array[i];\n"
    
    code += """
    }}
    
    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Unrolling factor: %d\\n", {unroll_factor});
    printf("CPU time used: %f seconds\\n", cpu_time_used);

    return 0;
}}
"""
    with open(f'unrolled_loop_{unroll_factor}.c', 'w') as f:
        f.write(code)

def main():
    unroll_factors = [1, 2, 4, 8, 16, 32]

    for factor in unroll_factors:
        generate_c_file(factor)
        print(f"Generated unrolled_loop_{factor}.c file")

if __name__ == "__main__":
    main()

