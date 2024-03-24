import socket
from keras.models import load_model
import numpy as np
from PIL import Image
import os

#TCP Client
if __name__ == '__main__':
    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
    client_sock.connect(('127.0.0.1', 26001))
    # Connect and receive file size info from server
    while True:
        file_info = client_sock.recv(1024)
        file_size = int.from_bytes(file_info, byteorder='little')
        received_data = b""
        print(file_size)
        while True:
            print("Receiving data...")
            data = client_sock.recv(
                )
            received_data += data
            if len(received_data) >= file_size:
                break

        save_path = 'C:/Users/user/Desktop/sample_test/c.png'
        with open(save_path, 'wb') as file:
            file.write(received_data)
        print(f"File saved: {save_path}")

        model = load_model(r'C:/Users/user/Downloads/my_model.hdf5')

        image_path = 'C:/Users/user/Desktop/sample_test/c.png'

        image = Image.open(image_path)
        image = image.resize((150, 150))
        image = np.array(image) / 255.0
        predictions = model.predict(np.expand_dims(image, axis=0))
        print(f"File name: {image_path}")

        if predictions[0] > 0.8:
            print("Pass")
            a = "Pass"
            client_sock.send(a.encode('utf-8'))
        else:
            print("Fail")
            b = "Fail"
            client_sock.send(b.encode('utf-8'))