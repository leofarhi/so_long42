import os, subprocess
# reader.py

# Créer un pipe nommé
def create_fifo(fifo):
    try:
        os.mkfifo(fifo)
        print(f"Pipe {fifo} created")
    except FileExistsError:
        print(f"Pipe {fifo} already exists")
def delete_fifo(fifo):
    os.remove(fifo)
    print(f"Pipe {fifo} deleted")

tests= ["test1", "test2", "test3"]

def main():
    FIFO_FILE = "myfifo"
    if not os.path.exists(FIFO_FILE):
        create_fifo(FIFO_FILE)
    
    with open(FIFO_FILE, 'w') as fifo:
        while True:
            if len(tests) == 0:
                break
            message = tests.pop(0)#input("Enter a message: ")
            if message == "exit":
                break
            fifo.write(message+ '\n')
            fifo.flush()
    delete_fifo(FIFO_FILE)
            
    

if __name__ == "__main__":
    main()