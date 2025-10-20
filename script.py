import subprocess
import os
import re

prog = 'cmake-build-debug/./cnfchk'

def time_script(dir):
    results = {}
    for dirs in os.listdir(dir):
        tot_parse_time, tot_ht_time, tot_e_time, tot_val_time = 0, 0, 0, 0
        count = 0
        for file in os.listdir(dir + dirs + '/'):
            try:
                print(file)
                result = subprocess.run(
                    [prog, str(dir + dirs + '/' + file)],
                    capture_output=True,
                    text=True,
                    check=True
                )

                output = result.stdout.strip()
                time_results = output.split('---TIME ANALYSIS---')[1].split('\n')
                #
                # parse_time, height_time, eval_time, val_time = time_results[1], time_results[2], time_results[3], time_results[4]
                tot_parse_time += int(re.search(r'(\d+)', time_results[1]).group(1))
                tot_ht_time += int(re.search(r'(\d+)', time_results[2]).group(1))
                tot_e_time += int(re.search(r'(\d+)', time_results[3]).group(1))
                tot_val_time += int(re.search(r'(\d+)', time_results[4]).group(1))
                print(time_results)

                count += 1

            except subprocess.CalledProcessError as e:
                    print("Error processing file")

        results[dirs] = [tot_parse_time/count, tot_ht_time/count, tot_e_time/count, tot_val_time/count]

    return results

if __name__ == '__main__':
    pass