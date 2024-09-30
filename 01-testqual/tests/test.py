import itertools
import os
import re
import subprocess

from pathlib import Path

def find_all_true_false(input_string):
    pattern = r'\b(true|false)\b'    
    matches = re.findall(pattern, input_string, re.IGNORECASE)

    return matches

def gen_cv_chars(elements=["*", "const", "[]"], required="char"):
    required_length = 1
    max_words = 5

    non_array_elements = [elem for elem in elements if elem != "[]"]
    array_elements = ["[]"]

    def has_duplicate_qualifiers(combination):
        seen = set()
        for elem in combination:
            if elem in seen:
                return True
            if elem in non_array_elements:
                seen.add(elem)
        return False

    def is_const_at_forbidden_indices(combination):
        if len(combination) > 0 and combination[0] == "const":
            return True 
        if len(combination) > 2 and combination[2] == "const":
            return True
        return False

    for length in range(max_words - required_length + 1):
        for combination in itertools.product(non_array_elements, repeat=length):
            if not has_duplicate_qualifiers(combination) and not is_const_at_forbidden_indices(combination):
                combined_string = ' '.join((required,) + combination).strip()
                if len(combined_string.split()) <= max_words:
                    yield combined_string

    for length in range(max_words - required_length):
        for combination in itertools.product(non_array_elements, repeat=length):
            if not has_duplicate_qualifiers(combination) and not is_const_at_forbidden_indices(combination):
                combined_string = ' '.join((required,) + combination + tuple(array_elements)).strip()
                if len(combined_string.split()) <= max_words:
                    yield combined_string

    for length in range(max_words - required_length):
        for combination in itertools.product(non_array_elements, repeat=length):
            if not has_duplicate_qualifiers(combination) and not is_const_at_forbidden_indices(combination):
                combined_string = ' '.join(("const", required) + combination + tuple(array_elements)).strip()
                if len(combined_string.split()) <= max_words:
                    yield combined_string

def get_combs(generator):
    return [comb for comb in generator]

def run_subprocess(cmd):
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
    out, _ = proc.communicate()
    return out.decode('utf-8')

def std_conversion_check(type1, type2, i_idx, j_idx):
    cpp_file=f"""
#include <iostream>
#include <type_traits>
#include <exception>

int main() {{
    bool res = false;
    try {{
        if constexpr (std::is_convertible_v<{type1}, {type2}>) {{
            res = true;
        }} else {{
            res = false;
        }}
    }} catch (const std::exception& e) {{
        res = false;
    }} catch (...) {{
        res = false;
    }}
    
    std::cout << std::boolalpha << res << std::endl; 
    return 0;
}}
"""

    gen_dir = "gen_test_dir"
    isExists = os.path.exists(gen_dir)
    if not isExists:
        os.mkdir(gen_dir)

    test_file = f"gentest_{i_idx}_{j_idx}.cpp"
    filepath = os.path.join(gen_dir, test_file)
    with open(filepath, 'w') as f:
        f.write(cpp_file)
    
    output_file = os.path.join(gen_dir, f"out_{i_idx}_{j_idx}")
    os.system(f"clang++ -std=c++17 {filepath} -o {output_file}")

    cmd = f"./{output_file}"
    result = subprocess.run([cmd], capture_output=True, text=True, check=True)
    output = result.stdout

    res =  find_all_true_false(output)

    return res[0]

if __name__ == "__main__":
    cwd = os.path.join(Path.cwd(), "tests")
    gen = gen_cv_chars()

    first_n_strings = get_combs(gen)
    second_n_strings=first_n_strings.copy()

    for i in range(len(first_n_strings)):
        for j in range(len(second_n_strings)):
            type1 = first_n_strings[i]
            type2 = second_n_strings[j]

            std_result = std_conversion_check(type1, type2, i, j)

            output = run_subprocess(f"{cwd}/../tq.out \"{type1}\" \"{type2}\"")
            matches = find_all_true_false(output)
            result = matches[0]

            if (result != std_result):
                print("error!")
                print(f"{type1=}, {type2=}, {result=}, {std_result=}, {i=}, {j=}")

