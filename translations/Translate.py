from bs4 import BeautifulSoup
import xml.etree.ElementTree as ET
import json
import os

source_file = "BottleInsp_en.ts"
dest_file = "BottleInsp_ru.ts"
ru_lang_dict_json_file = "BottleInsp_ru_dict.json"

def CreateLanguageFile(source_file, lang_dict_json_file):
    # Find all unique words
    with open(source_file, 'r') as f:
        data = f.read()

    bs_data = BeautifulSoup(data, "xml")
    all_words = bs_data.find_all('source')
    all_words = [s.text.replace("<source>", "").replace("</source>", "") for s in all_words]
    all_unique_words = set(all_words)

    # read file lang_dic_json_file if exist
    if os.path.exists(lang_dict_json_file):
        f = open(lang_dict_json_file, 'r', encoding='utf-8')
        all_unique_words_dict = json.load(f)
        f.close()
    else:
        all_unique_words_dict = {}

    # append new words to dict file
    for w in all_unique_words:
        if w in all_unique_words_dict.keys():
            continue
        all_unique_words_dict[w] = w

    # json_object = json.dumps(all_unique_words_dict, indent=4)
    # Writing to sample.json
    with open(lang_dict_json_file, "w", encoding='utf-8') as outfile:
        json.dump(all_unique_words_dict, outfile, ensure_ascii=False, indent=4)

def ApplyDicToTsFile(source_file, dest_file):
    # read json dict file
    f = open(source_file, 'r', encoding='utf-8')
    all_unique_words_dict = json.load(f)
    f.close()


    tree = ET.parse(dest_file)
    root = tree.getroot()
    # Iterate through all elements with the specified tag
    parent_tag = "message"
    tag = "source"

    
    for parent in root.iter(parent_tag):
        for i, elem in enumerate(parent):
            if elem.tag != tag:
                continue
            if elem.text in all_unique_words_dict.keys():
                # Find the next sibling
                try:
                    next_sibling = parent[i + 1]
                except:
                    continue

                # Remove the attribute
                try:
                    next_sibling.attrib.pop("type")
                except:
                    pass
                next_sibling.text = all_unique_words_dict[elem.text]

    
    # Write the modified XML to a file
    tree.write(dest_file, encoding='utf-8', xml_declaration=True)
    return

CreateLanguageFile(source_file, ru_lang_dict_json_file)

# ApplyDicToTsFile(ru_lang_dict_json_file, dest_file)





