import tkinter as tk
import threading

def show_clients():
    with open("client_info.txt", "r") as file:
        clients = file.read()
    
    # Clear previous content in the scrollable frame
    for widget in frame_clients.winfo_children():
        widget.destroy()
    
    # Display the clients in the scrollable frame
    for client in clients.splitlines():
        label_client = tk.Label(frame_clients, text=client)
        label_client.pack(anchor="w")  # Align to the left

def run_command(command):
    command_map = {
        "deposit": handle_deposit,
        "withdraw": handle_withdraw,
        "find_client": handle_find_client,
        "save_changes": handle_save_changes,
        "add_client": handle_add_client,
    }

    action = command[1]
    if action in command_map:
        command_map[action](command)
    else:
        label_result.config(text="Unknown command.")

def handle_deposit(command):
    account_number = command[2]
    amount = float(command[3])
    clients = read_clients()

    for i, client_info in enumerate(clients):
        if client_info[2] == account_number:
            current_balance = float(client_info[3])
            new_balance = current_balance + amount
            client_info[3] = str(new_balance)
            clients[i] = client_info
            write_clients(clients)
            label_result.config(text=f"Deposit successful! New balance: {new_balance}")
            return
    
    label_result.config(text="Account number not found.")

def handle_withdraw(command):
    account_number = command[2]
    amount = float(command[3])
    clients = read_clients()

    for i, client_info in enumerate(clients):
        if client_info[2] == account_number:
            current_balance = float(client_info[3])
            if current_balance >= amount:
                new_balance = current_balance - amount
                client_info[3] = str(new_balance)
                clients[i] = client_info
                write_clients(clients)
                label_result.config(text=f"Withdrawal successful! New balance: {new_balance}")
            else:
                label_result.config(text="Insufficient balance")
            return

    label_result.config(text="Account number not found.")

def handle_find_client(command):
    account_number = command[2]
    clients = read_clients()

    for client_info in clients:
        if client_info[2] == account_number:
            label_result.config(text=f"Client found: {client_info[0]}, SSN: {client_info[1]}, Balance: {client_info[3]}")
            return

    label_result.config(text="Client not found.")

def handle_save_changes(command):
    label_result.config(text="Changes saved successfully!")

def handle_add_client(command):
    name = command[2]
    ssn = command[3]
    account_number = command[4]
    amount = command[5]
    clients = read_clients()

    new_client_info = [name, ssn, account_number, amount]
    clients.append(new_client_info)
    write_clients(clients)
    label_result.config(text="Client added successfully!")

def read_clients():
    with open("client_info.txt", "r") as file:
        return [line.strip().split() for line in file.readlines()]

def write_clients(clients):
    with open("client_info.txt", "w") as file:
        for client_info in clients:
            file.write(' '.join(client_info) + '\n')

def clear_entries():
    entry_name.delete(0, tk.END)
    entry_ssn.delete(0, tk.END)
    entry_account.delete(0, tk.END)
    entry_amount.delete(0, tk.END)

def submit():
    account_number = entry_account.get()
    name = entry_name.get()
    ssn = entry_ssn.get()
    amount = entry_amount.get()
    selected_option = var.get()

    if selected_option in [1, 2, 5] and (not account_number.isnumeric() or not amount.replace('.', '', 1).isdigit()):
        label_result.config(text="Account Number and Amount must be numeric!")
        return

    if selected_option == 1:  # Deposit
        command = ["./main", "deposit", account_number, amount]
    elif selected_option == 2:  # Withdraw
        command = ["./main", "withdraw", account_number, amount]
    elif selected_option == 3:  # Show all clients
        show_clients()
        return
    elif selected_option == 4:  # Find a client
        command = ["./main", "find_client", account_number]
    elif selected_option == 5:  # Add new client
        command = ["./main", "add_client", name, ssn, account_number, amount] 
    elif selected_option == 6:  # Save changes
        command = ["./main", "save_changes"]
        clear_entries()

    threading.Thread(target=run_command, args=(command,)).start()

root = tk.Tk()
root.title("Our Bank App")

label_account = tk.Label(root, text="Enter Account Number (for new client)")
label_account.pack(padx=20, pady=10)
entry_account = tk.Entry(root)
entry_account.pack(padx=10, pady=5)

label_name = tk.Label(root, text="Enter Client Name (for new client)")
label_name.pack(padx=20, pady=10)
entry_name = tk.Entry(root)
entry_name.pack(padx=10, pady=5)

label_ssn = tk.Label(root, text="Enter Client SSN (for new client)")
label_ssn.pack(padx=20, pady=10)
entry_ssn = tk.Entry(root)
entry_ssn.pack(padx=10, pady=5)

label_amount = tk.Label(root, text="Enter Amount")
label_amount.pack(padx=20, pady=10)
entry_amount = tk.Entry(root)
entry_amount.pack(padx=10, pady=5)

label_option = tk.Label(root, text="Choose one option:")
label_option.pack(padx=10, pady=5)

var = tk.IntVar()
var.set(1)
radio1 = tk.Radiobutton(root, text="Deposit", variable=var, value=1)
radio1.pack(padx=10, pady=2)
radio2 = tk.Radiobutton(root, text="Withdraw", variable=var, value=2)
radio2.pack(padx=10, pady=2)
radio3 = tk.Radiobutton(root, text="Show all clients", variable=var, value=3)
radio3.pack(padx=10, pady=2)
radio4 = tk.Radiobutton(root, text="Find client by account number", variable=var, value=4)
radio4.pack(padx=10, pady=2)
radio5 = tk.Radiobutton(root, text="Add new client", variable=var, value=5)
radio5.pack(padx=10, pady=2)
radio6 = tk.Radiobutton(root, text="Save changes", variable=var, value=6)
radio6.pack(padx=10, pady=2)

button = tk.Button(root, text="Submit", command=submit)
button.pack(padx=10, pady=10)

frame_scroll = tk.Frame(root)
frame_scroll.pack(padx=20, pady=20)

canvas = tk.Canvas(frame_scroll)
scrollbar = tk.Scrollbar(frame_scroll, orient="vertical", command=canvas.yview)
frame_clients = tk.Frame(canvas)

frame_clients.bind(
    "<Configure>",
    lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
)

canvas.create_window((0, 0), window=frame_clients, anchor="nw")
canvas.configure(yscrollcommand=scrollbar.set)

canvas.pack(side="left", fill="both", expand=True)
scrollbar.pack(side="right", fill="y")

label_result = tk.Label(root, text="")
label_result.pack(padx=20, pady=20)

root.mainloop()
