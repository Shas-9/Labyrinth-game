import tkinter as tk

from tkinter import messagebox
from functools import partial

root = tk.Tk()
root.geometry("300x200")
root.title("My awesome app")
frame = tk.Frame(root)
frame.pack()

def custom_message(message: str):
  messagebox.showinfo("Title of messagebox", message)

button = tk.Button(frame, text="Quit App", fg="red", command=quit)

msg_box_btn = tk.Button(frame, text="Show Message!", command=partial(custom_message, "Our message goes here!"))
button.pack(side=tk.LEFT)
msg_box_btn.pack(side=tk.RIGHT)

root.mainloop()