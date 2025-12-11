import asyncio
import threading
import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
from bleak import BleakClient

# --- CONFIGUREER HIER ---
DEVICE_ADDRESS = "F9:64:7C:95:5E:23"
CHAR_UUID = "19b10001-e8f2-537e-4f6c-d104768a1215"
LEFT_PHOTO = "Afbeelding1.png"   # linkerfoto
RIGHT_PHOTO = "me.jpg"           # rechterfoto
# -------------------------

ble_loop = asyncio.new_event_loop()
ble_loop_thread = threading.Thread(target=ble_loop.run_forever, daemon=True)
ble_loop_thread.start()

client = None
client_lock = threading.Lock()

def run_coro(coro):
    return asyncio.run_coroutine_threadsafe(coro, ble_loop)

# --- Async BLE routines ---
async def async_connect():
    global client
    c = BleakClient(DEVICE_ADDRESS)
    await c.connect(timeout=10)
    if not c.is_connected:
        raise RuntimeError("Kon niet verbinden")
    with client_lock:
        global client
        client = c
    return True

async def async_write(number: int):
    with client_lock:
        c = client
    if c is None or not c.is_connected:
        raise RuntimeError("Niet verbonden")
    await c.write_gatt_char(CHAR_UUID, bytes([number]))

async def async_disconnect():
    global client
    with client_lock:
        c = client
        client = None
    if c:
        try:
            await c.disconnect()
        except Exception:
            pass

# --- Tkinter GUI ---
class BLEGui:
    def __init__(self, root):
        self.root = root
        root.title("BLE Controller")
        root.state("zoomed")  # fullscreen

        screen_width = root.winfo_screenwidth()
        screen_height = root.winfo_screenheight()

        # Container frame
        self.container = tk.Frame(root, bg="#0a1e3b")
        self.container.pack(fill="both", expand=True)
        self.container.columnconfigure((0,1), weight=1)
        self.container.rowconfigure(2, weight=1)  # foto's nemen meeste ruimte

        # Titel
        title_font = max(24, screen_height // 30)
        title = tk.Label(self.container, text="BLE Controller",
                         font=("Segoe UI", title_font, "bold"),
                         fg="#ffffff", bg="#0a1e3b")
        title.grid(row=0, column=0, columnspan=2, pady=(20,10))

        # Status
        status_font = max(14, screen_height // 90)
        self.status_var = tk.StringVar(value="Niet verbonden")
        status_label = tk.Label(self.container, textvariable=self.status_var,
                                fg="#a8d08d", bg="#0a1e3b",
                                font=("Segoe UI", status_font))
        status_label.grid(row=1, column=0, columnspan=2, pady=(0,10))

        # Foto canvas links
        canvas_width = screen_width//3
        canvas_height = int(screen_height*0.4)
        self.left_photo_canvas = tk.Canvas(self.container, width=canvas_width, height=canvas_height,
                                           highlightthickness=0, bg="#0a1e3b")
        self.left_photo_canvas.grid(row=2, column=0, padx=20, pady=20, sticky="n")
        self._load_photo(self.left_photo_canvas, LEFT_PHOTO)

        # Foto canvas rechts
        self.right_photo_canvas = tk.Canvas(self.container, width=canvas_width, height=canvas_height,
                                            highlightthickness=0, bg="#0a1e3b")
        self.right_photo_canvas.grid(row=2, column=1, padx=20, pady=20, sticky="n")
        self._load_photo(self.right_photo_canvas, RIGHT_PHOTO)

        # Knoppenframe onder de foto's
        btn_frame = tk.Frame(self.container, bg="#0a1e3b")
        btn_frame.grid(row=3, column=0, columnspan=2, pady=(0,20))
        for i in range(2):
            btn_frame.columnconfigure(i, weight=1)
        for i in range(3):
            btn_frame.rowconfigure(i, weight=1)

        # Knoppen stijl
        style = ttk.Style(root)
        style.theme_use('clam')
        btn_font = max(16, screen_height // 60)
        style.configure("TButton",
                        font=("Segoe UI", btn_font),
                        padding=15,
                        background="#1e3b70",
                        foreground="white",
                        borderwidth=1)
        style.map("TButton",
                  background=[('active', '#2b5cad')],
                  foreground=[('disabled', '#888888')])

        # Verbinden / Ontkoppelen
        self.connect_btn = ttk.Button(btn_frame, text="Verbind", command=self.connect_device)
        self.connect_btn.grid(row=0, column=0, padx=20, pady=10, sticky="nsew")
        self.disconnect_btn = ttk.Button(btn_frame, text="Ontkoppel", command=self.disconnect_device)
        self.disconnect_btn.grid(row=0, column=1, padx=20, pady=10, sticky="nsew")

        # Send knoppen
        self.stop_btn = ttk.Button(btn_frame, text="Stop", command=lambda: self.send_number(0))
        self.stop_btn.grid(row=1, column=0, padx=20, pady=10, sticky="nsew")
        self.start_btn = ttk.Button(btn_frame, text="Start", command=lambda: self.send_number(1))
        self.start_btn.grid(row=1, column=1, padx=20, pady=10, sticky="nsew")
        self.supercurve_btn = ttk.Button(btn_frame, text="Supercurve", command=lambda: self.send_number(2))
        self.supercurve_btn.grid(row=2, column=0, padx=20, pady=10, sticky="nsew")
        self.straight_btn = ttk.Button(btn_frame, text="Straight", command=lambda: self.send_number(3))
        self.straight_btn.grid(row=2, column=1, padx=20, pady=10, sticky="nsew")
        self.tokyo_btn = ttk.Button(btn_frame, text="Tokyo Drift", command=lambda: self.send_number(4))
        self.tokyo_btn.grid(row=3, column=0, columnspan=2, padx=20, pady=10, sticky="nsew")

        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        self._set_send_buttons_state("disabled")

    # --- Foto laden ---
    def _load_photo(self, canvas, path):
        canvas.delete("all")
        try:
            img = Image.open(path)
            canvas_width = canvas.winfo_reqwidth()
            canvas_height = canvas.winfo_reqheight()
            img.thumbnail((canvas_width, canvas_height))
            photo_tk = ImageTk.PhotoImage(img)
            canvas.create_image(canvas_width//2, canvas_height//2, image=photo_tk)
            # Houd referentie vast
            if canvas == self.left_photo_canvas:
                self.left_photo_tk = photo_tk
            else:
                self.right_photo_tk = photo_tk
        except Exception:
            canvas.create_rectangle(10,10,canvas.winfo_reqwidth()-10,canvas.winfo_reqheight()-10, fill="#1e3b70")
            canvas.create_text(canvas.winfo_reqwidth()//2, canvas.winfo_reqheight()//2,
                               text="Geen\nFoto", font=("Segoe UI", 16), fill="white")

    # --- BLE functies ---
    def connect_device(self):
        self.status_var.set(f"Verbinden met {DEVICE_ADDRESS}...")
        future = run_coro(async_connect())
        def cb(f):
            try:
                f.result()
                self.status_var.set(f"Verbonden met {DEVICE_ADDRESS}")
                self._set_send_buttons_state("normal")
            except Exception as exc:
                self.status_var.set(f"Verbindingsfout: {exc}")
                self._set_send_buttons_state("disabled")
        future.add_done_callback(lambda f: self.root.after(0, lambda: cb(f)))

    def disconnect_device(self):
        future = run_coro(async_disconnect())
        def cb(f):
            try:
                f.result()
            finally:
                self.status_var.set("Niet verbonden")
                self._set_send_buttons_state("disabled")
        future.add_done_callback(lambda f: self.root.after(0, lambda: cb(f)))

    def send_number(self, n:int):
        self.status_var.set(f"Verzenden: {n} ...")
        future = run_coro(async_write(n))
        def cb(f):
            try:
                f.result()
                self.status_var.set(f"Verzonden: {n}")
            except Exception as exc:
                self.status_var.set(f"Fout bij verzenden: {exc}")
        future.add_done_callback(lambda f: self.root.after(0, lambda: cb(f)))

    def _set_send_buttons_state(self, state):
        for b in (self.stop_btn, self.start_btn, self.supercurve_btn, self.straight_btn, self.tokyo_btn):
            b['state'] = state

    def on_close(self):
        try:
            run_coro(async_disconnect()).result(timeout=3)
        except Exception:
            pass
        try:
            ble_loop.call_soon_threadsafe(ble_loop.stop)
        except Exception:
            pass
        self.root.destroy()

def main():
    root = tk.Tk()
    app = BLEGui(root)
    root.mainloop()

if __name__ == "__main__":
    main()
