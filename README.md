# Spider - A Simple Web Image Scraper

Spider is a Python script that allows you to extract all images from a website, optionally doing so recursively, by providing a URL as a parameter

## Features
**- Recursive Downloading (-r):** Spider can download images not just from the URL provided, but also from any linked pages, recursively.

**- Depth Specification (-l [N]):** You can specify the depth of recursion for downloads. If not specified, the default depth is 5.

**- Custom Save Path (-p [PATH]):** Specify the path where the downloaded images will be saved. If not specified, images will be saved in a ./data/ directory by default.

## Supported Image Formats  

- .jpg/.jpeg
- .png
- .gif
- .bmp

## Usage

For example, to scrape images from example.com and save them to the ./images/ directory, you would use:
```sh
./spider -p ./images/ https://www.example.com/
```
