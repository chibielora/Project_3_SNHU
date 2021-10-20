import re
import string

def create_dictionary(filename):
    collection = dict()
    # Open file for reading
    try:
        file = open(filename, "r")
    except FileNotFoundError:
        print("Unable to find file: " + filename)
        return collection
    
    for item in file:
        # Set default to lowercase
        item = item.strip().lower()
        
        # Check if item is already on dictionary
        if item in collection:
            # If already in, add 1 to existing
            collection[item] = collection[item] + 1
        else:
            # If not, item won't be added
            collection[item] = 1
    file.close()
    return collection

# Method to call for amount of each item
def get_frequency_all():
    collection = create_dictionary("input.txt")
    for key in list (collection.keys()):
        print(key.capitalize() + ":", collection[key])

# Method to count how many times item has appeared by inputting item_name
def get_frequency_one(item_name):
    # Set default to lowecase
    item_name = item_name.lower()
    # Open in read mode
    collection = create_dictionary("input.txt")
    if item_name in collection:
        return collection[item_name]
    else:
        return 0

# Method to create data for histogram in frequency.dat
def write_dictionary_to_file():
    collection = create_dictionary("input.txt")
    # Create file for writing
    frequency = open("frequency.dat", "w")

    # Write key-value pairs into frequency.dat
    for key in list (collection.keys()):
        # Format and adds new line
        frequency.write(str(key.capitalize()) + " " + str(collection[key]) + "\n")

    frequency.close()