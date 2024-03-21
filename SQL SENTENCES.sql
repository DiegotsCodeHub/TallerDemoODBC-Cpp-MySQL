CREATE DATABASE test;

USE test;

CREATE TABLE ejemplo (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(255)
);

INSERT INTO ejemplo (nombre) VALUES ('Juan'), ('María'), ('Pedro');