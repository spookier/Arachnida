import sys
import os
import requests
import argparse
import re
import urllib.parse


parser = argparse.ArgumentParser(description="A script for downloading images.", epilog="Example usage: python3 spider.py -r -l 5 -p ./images/")
parser.add_argument("-r", action="store_true", help="recursively download images")
parser.add_argument("-l", metavar="DEPTH", type=int, default=5, help="maximum depth level of the recursive download")
parser.add_argument("-p", metavar="PATH", default="./data/", help="path to save images")
parser.add_argument("url", help="The URL to process")



def req_data(url):
    data = None
    data = requests.get(url)
    if data == None:
        return (-1)
    return (data)


def make_folder(path):
    if(os.path.exists(path)):
        return(0)
    else:
    	os.mkdir(path)


def save_image(img_url, download_path):
	image = requests.get(img_url, stream=True)
	if image.status_code == 200:
		file_name = os.path.basename(img_url)
		file_path = os.path.join(download_path, file_name)
		with open(file_path, "wb") as img:
			for chunk in image.iter_content(chunk_size=8192):
				if chunk:
					img.write(chunk)
		print(f"Image found -> {file_name}")
	else:
		print(f"Error. Image found but failed to download. {img_url}")


def abs_to_relative_url(url_data, url):
	if url.startswith("http") or url.startswith("https://"):
		return (url)
	else:
		url = urllib.parse.urljoin(url_data.url, url)
		return (url)


def download_images(url_data, recursive_download, level_depth, download_path):
	extensions = [".jpg", ".jpeg", ".png", ".gif", ".bmp"]
	img_urls = re.findall(r'<img[^>]+src="([^">]+)', url_data.text)
	for url in img_urls:
		url = abs_to_relative_url(url_data, url)
		for ext in extensions:
			if url.endswith(ext):
				#print(url)
				save_image(url, download_path)
				break


def get_link_data(url):
	url_data = None
	url_data = req_data(url)
	if url_data.status_code >= 200 and url_data.status_code < 300:
		return(url_data)
	else:
		print("Error. Invalid URL.")
		exit(-1)