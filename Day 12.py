#!/usr/bin/env python3
import os
import sys
import subprocess

NOTES_DIRECTORY = 'notes'
EDITOR = '/Applications/iA Writer.app/'
def create_note(title):
    filename = f'{title}.md'
    file_path = os.path.join(NOTES_DIRECTORY, filename)
    if not os.path.exists(NOTES_DIRECTORY):
        os.makedirs(NOTES_DIRECTORY)
    if not os.path.exists(file_path):
        with open(file_path, 'w') as file:
            file.write(f'# {title}\n\n')
    subprocess.run([EDITOR, file_path])

def search_notes(search_term):
    if not os.path.exists(NOTES_DIRECTORY):
        print(f'{NOTES_DIRECTORY} directory does not exist.')
        return
    for filename in os.listdir(NOTES_DIRECTORY):
        if filename.endswith('.md'):
            with open(os.path.join(NOTES_DIRECTORY, filename), 'r') as file:
                contents = file.read()
                if search_term in contents:
                    print(filename)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python note_utility.py <command> <args>')
    else:
        command = sys.argv[1]

        if command == 'create':
            title = sys.argv[2]
            create_note(title)
        elif command == 'search':
            search_term = sys.argv[2]
            search_notes(search_term)
        else:
            print('Invalid command')
