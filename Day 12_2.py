import subprocess

filename = "example.txt"

# Open the file in iA Writer
editor_process = subprocess.Popen(["open", "-a", "iA Writer", filename])

# Wait for the editor to close
editor_process.wait()

# Focus back to the terminal
subprocess.Popen(["osascript", "-e", "tell application \"Kitty\" to activate"])
