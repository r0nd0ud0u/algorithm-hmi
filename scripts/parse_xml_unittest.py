import xml.etree.ElementTree as ET
from argparse import ArgumentParser

if __name__ == '__main__':
    # Parse command line argument arguments
    parser = ArgumentParser()
    parser.add_argument('-xml_file',
                        type=str,
                        help='Choose the target directory ',
                        const=1,
                        nargs='?',
                        default='.\\output.xml')
    mytree = ET.parse(parser.parse_args().xml_file)
    myroot = mytree.getroot()
    for child in myroot:
        if child.attrib['failures'] == '1':
            print('Failed {}'.format(child.attrib))
        else :
            print('all tests({}) OK'.format(len(child)))

