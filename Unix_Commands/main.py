import os
# Define a function to display a menu of options
def display_menu():
    print("Welcome to the Bash tutorial!")
    print("1. List files in the current directory (ls)")
    print("2. Create a new directory (mkdir)")
    print("3. Change to a different directory (cd)")
    print("4. View the contents of a file (cat)")
    print("5. Exit")

# Define a function to prompt the user to enter a command
def prompt_command():
    command = input("Enter the Linux command: ")
    os.system(command)

# Main program loop
while True:
    display_menu()
    choice = input("Enter your choice: ")
    if choice == "1":
        print("The Linux command for listing files in the current directory is 'ls'")
        prompt_command()
    elif choice == "2":
        print("The Linux command for creating a new directory is 'mkdir'")
        prompt_command()
    elif choice == "3":
        print("The Linux command for changing to a different directory is 'cd'")
        prompt_command()
    elif choice == "4":
        print("The Linux command for viewing the contents of a file is 'cat'")
        prompt_command()
    elif choice == "5":
        break
    else:
        print("Invalid choice. Please try again.")
