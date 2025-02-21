# README.md Content

# PC Parts & Essentials Shop

# Features:

1) Terminal-based menu with categorized sort-by functions (can be sorted by subcategories) to display products.

    **Product Categories & Subcategories:**

    a) GPUs
        - Brands: AMD, Nvidia
        - Manufacturers: GIGABYTE, MSI, ASUS, ZOTAC, PALIT, ACER, ASROCK, EVGA, SAPPHIRE
        - Series: Nvidia (10 Series, 20 Series, 30 Series, 40 Series, 50 Series), AMD (RX 500, RX Vega, RX 5000, RX 6000, RX 7000)
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    b) CPUs
        - Brands: AMD, Intel
        - Tier: Intel (Core i3, Core i5, Core i7, Core i9), AMD (Ryzen 3, Ryzen 5, Ryzen 7, Ryzen 9, Ryzen Threadripper)
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    c) RAM
        - Types: DDR3, DDR4, DDR5
        - Capacity: 4GB, 8GB, 16GB, 32GB, 64GB+
        - Speed: 2400MHz, 3200MHz, 3600MHz, 4000MHz+
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    d) Storage
        - Type: HDD, SSD, NVMe M.2
        - Capacity: 128GB, 256GB, 512GB, 1TB, 2TB+
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    e) Motherboards
        - Chipsets: Intel (Z790, B760, H670, etc.), AMD (X670, B650, B550, X570, etc.)
        - Form Factor: ATX, Micro-ATX, Mini-ITX
        - Socket: Intel (LGA 1200, LGA 1700, etc.), AMD (AM4, AM5, TR4)
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    f) Power Supplies (PSU)
        - Wattage: 450W – 550W, 600W – 750W, 800W – 1000W, 1000W+
        - Efficiency Rating: 80+ Bronze, 80+ Silver, 80+ Gold, 80+ Platinum
        - Modularity: Non-modular, Semi-modular, Fully modular
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    g) PC Cases
        - Form Factor Support: ATX, Micro-ATX, Mini-ITX
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    h) Cooling
        - Types: Air Coolers, AIO Liquid Coolers (120mm, 240mm, 360mm), Custom Water Cooling Kits
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

    i) Pre-builts
        - Sort by: Price (Ascending/Descending), QTY (Ascending/Descending)

2) Shopping Cart System that can hold the products and print a receipt to the console 
    - Should be usable more than once in program runtime.

3) File handling
    - A text file named `inventory.txt` should be prepopulated with the products mentioned if the text file does not exist.
    - Update the text file when products are bought by the user (change QTY).

4) Error handling
    - Make sure there are no bugs in the menu where the user can break the program at runtime.

## Requirements:
- Program should be written in C++.
- Program should use these algorithms (user-defined):
    1) Binary Search Tree Algorithm
    2) Merge Sort Algorithm
    3) Quick Sort Algorithm.


HOW TO COMPILE AND RUN

1. Fork the repo and open your terminal in your chosen IDE

2. Make sure you are in the pc-parts-shop directory
example command:
cd "c:\Users\Desmond Que\GitRepos\Group8-Act2-Divide-Conquer\Group8-Act2-Divide-Conquer\pc-parts-shop"

3. Run this command while in the pc-parts-shop directory
g++ -I src/ src/main.cpp src/utils/file_handler.cpp src/algorithms/merge_sort.cpp src/algorithms/quick_sort.cpp -o bin/main.exe; if ($?) { .\bin\main.exe }