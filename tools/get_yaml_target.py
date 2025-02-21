import yaml
import os
import sys

def get_yaml_target(yaml_file):
    # Get the current working directory
    current_dir = os.getcwd()
    yaml_path = os.path.join(current_dir, yaml_file)
    
    with open(yaml_path, 'r') as file:
        data = yaml.safe_load(file)
        target_path = data.get('options', {}).get('target_path', 'target_path not found')

        # Drop the first folder from the path - rom/ or assets/
        parts = target_path.split(os.sep)
        if len(parts) > 1:
            target_path = os.sep.join(parts[1:])
        
        return target_path

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python tools/get_yaml_target.py configs/<config_file>.yaml")
        sys.exit(1)
    
    yaml_file = sys.argv[1]
    target_path = get_yaml_target(yaml_file)
    print(target_path)
