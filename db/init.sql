CREATE DATABASE testbed;

CREATE TABLE datapoints (
    time TIMESTAMP,
    PVPositive REAL,
    PVNegative REAL,
    BoardPositive REAL, 
    BattPositive REAL,
    PVCurrent REAL,
    BoardCurrent REAL,
    BattCurrent REAL,
    temp REAL,
    site_id serial PRIMARY KEY
);