
import csv

# Function to read data from CSV file
def read_student_records(filename):
    student_records = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            student_records.append(row)
    return student_records

# Function to calculate the average age of students
def calculate_average_age(student_records):
    total_age = 0
    num_students = len(student_records)
    for student in student_records:
        total_age += int(student[3])  # Assuming age is at index 3
    average_age = total_age / num_students
    return round(average_age, 2)

# Function to calculate the average grade level of students
def calculate_average_grade_level(student_records):
    total_grade_level = 0
    num_students = len(student_records)
    for student in student_records:
        total_grade_level += int(student[5])  # Assuming grade level is at index 5
    average_grade_level = total_grade_level / num_students
    return round(average_grade_level, 2)

# Function to find students with the highest average score
def find_students_with_highest_average_score(student_records):
    max_average_score = max(float(student[6]) for student in student_records)  # Assuming average score is at index 6
    students_highest_average = [student for student in student_records if float(student[6]) == max_average_score]
    return students_highest_average

# Function to find students with the lowest average score
def find_students_with_lowest_average_score(student_records):
    min_average_score = min(float(student[6]) for student in student_records)  # Assuming average score is at index 6
    students_lowest_average = [student for student in student_records if float(student[6]) == min_average_score]
    return students_lowest_average

# Function to count the number of male and female students
def count_male_female_students(student_records):
    num_male = sum(student[4].lower() == 'male' for student in student_records)  # Assuming gender is at index 4
    num_female = len(student_records) - num_male
    return num_male, num_female

# Main program
if __name__ == '__main__':
    # Read the data from the CSV file
    file_names = ["student-records-1.csv", "student-records-2.csv", "student-records-3.csv"]
    for file_name in file_names:
        student_records = read_student_records(file_name)

        # Calculate and display the average age of the students
        average_age = calculate_average_age(student_records)
        print(f"Average Age of Students: {average_age}")

        # Calculate and display the average grade level of the students
        average_grade_level = calculate_average_grade_level(student_records)
        print(f"Average Grade Level of Students: {average_grade_level}")

        # Find and display the student(s) with the highest average score
        students_highest_average = find_students_with_highest_average_score(student_records)
        print("Student(s) with Highest Average Score:")
        for student in students_highest_average:
            print(f"- Name: {student[1]} {student[2]}")  # Assuming first name is at index 1 and last name is at index 2
            print(f"  Average Score: {student[6]}")  # Assuming average score is at index 6

        # Find and display the student(s) with the lowest average score
        students_lowest_average = find_students_with_lowest_average_score(student_records)
        print("Student(s) with Lowest Average Score:")
        for student in students_lowest_average:
            print(f"- Name: {student[1]} {student[2]}")  # Assuming first name is at index 1 and last name is at index 2
            print(f"  Average Score: {student[6]}")  # Assuming average score is at index 6

        # Count and display the number of male and female students
        num_male, num_female = count_male_female_students(student_records)
        print(f"Number of Male Students: {num_male}")
        print(f"Number of Female Students: {num_female}")

        print()  # Add a blank line between different data sets
