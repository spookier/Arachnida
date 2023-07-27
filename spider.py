from utils import *

def execute_program():
	options = parser.parse_args()
    
    # Default options
	recursive_download = False
	level_depth = 5
	download_path = "/.data/"
    
	if options.url:
		url = options.url
	elif options.url is None:
		print("Error. No URL specified.")
		exit(-1)
	if options.r:
		recursive_download = options.r
	if options.l:
		level_depth = options.l
	if options.p:
		download_path = options.p
		make_folder(download_path)
	
	url_data = get_link_data(url)
	image_count = download_images(url_data, recursive_download, level_depth, download_path)
	print("--------------------------------------")
	print(f"Total images found = [{image_count}]")
	print("--------------------------------------")


def main():
	execute_program()


if __name__ == "__main__":
  main()