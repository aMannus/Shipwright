#!/usr/bin/env python3

import os, sys, shutil
import shutil
from rom_info import Z64Rom
import rom_chooser
import subprocess
import argparse

def PreProcessAssets(rom, xmlOutputPath):
    xmlPathToProcess = "../soh/assets/xml/" + rom.version.xml_ver + "/"
    print("xmlPathToProcess: " + xmlPathToProcess + " xmlOutputPath: " + xmlOutputPath)

    if os.path.exists(xmlOutputPath):
        shutil.rmtree(xmlOutputPath)
    os.makedirs(xmlOutputPath)

    for root, dirs, files in os.walk(xmlPathToProcess):
        for file in files:
            if file.endswith(".xml"):
                if file == "nintendo_rogo_static.xml":
                    with open(os.path.join(root, file), "r") as f:
                        lines = f.readlines()

                    for i in range(len(lines)):
                        if "nintendo_rogo_static_Tex_000000" in lines[i]:
                            format = lines[i].split("Format=\"")[1].split("\"")[0]
                            width = int(lines[i].split("Width=\"")[1].split("\"")[0])
                            height = int(lines[i].split("Height=\"")[1].split("\"")[0]) // 16
                            offset = int(lines[i].split("Offset=\"")[1].split("\"")[0], 16)
                            lines[i] = ""

                            for j in range(16):
                                line = "         <Texture Name=\"nintendo_rogo_static_Tex_T{}\" OutName=\"tex_{:08x}\" Format=\"{}\" Width=\"{}\" Height=\"{}\" Offset=\"0x{:08x}\"/>\r".format(j, offset + j * width * height, format, width, height, offset + j * width * height)
                                lines.insert(i + j, line)

                    os.makedirs(os.path.join(root.replace(xmlPathToProcess, xmlOutputPath)), exist_ok=True)
                    with open(os.path.join(root.replace(xmlPathToProcess, xmlOutputPath), file), "w") as f:
                        f.writelines(lines)
                else:
                    os.makedirs(os.path.join(root.replace(xmlPathToProcess, xmlOutputPath)), exist_ok=True)
                    shutil.copyfile(os.path.join(root, file), os.path.join(root.replace(xmlPathToProcess, xmlOutputPath), file))

def BuildOTR(xmlPath, rom, zapd_exe=None):
    shutil.copytree("assets", "Extract/assets")

    if not zapd_exe:
        zapd_exe = "x64\\Release\\ZAPD.exe" if sys.platform == "win32" else "../ZAPDTR/ZAPD.out"

    exec_cmd = [zapd_exe, "ed", "-i", xmlPath, "-b", rom, "-fl", "CFG/filelists",
            "-o", "placeholder", "-osf", "placeholder", "-gsf", "1",
            "-rconf", "CFG/Config.xml", "-se", "OTR", "--otrfile", 
            "oot-mq.otr" if Z64Rom.isMqRom(rom) else "oot.otr"]

    print(exec_cmd)
    exitValue = subprocess.call(exec_cmd)
    if exitValue != 0:
        print("\n")
        print("Error when building the OTR file...", file=os.sys.stderr)
        print("Aborting...", file=os.sys.stderr)
        print("\n")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-z", "--zapd", help="Path to ZAPD executable", dest="zapd_exe", type=str)
    parser.add_argument("rom", help="Path to the rom", type=str, nargs="?")
    parser.add_argument("--non-interactive", help="Runs the script non-interactively for use in build scripts.", dest="non_interactive", action="store_true")

    args = parser.parse_args()

    rom_paths = [ args.rom ] if args.rom else rom_chooser.chooseROM(args.non_interactive)
    for rom_path in rom_paths:
        rom = Z64Rom(rom_path)

        if (os.path.exists("Extract")):
            shutil.rmtree("Extract")

        tempXmlPath = "../soh/assets/xml_temp/"
        PreProcessAssets(rom, tempXmlPath)

        # save xml folder as xml_safe
        if (os.path.exists("../soh/assets/xml_safe")):
            shutil.rmtree("../soh/assets/xml_safe")
        shutil.copytree("../soh/assets/xml", "../soh/assets/xml_safe")

        # copy temp xml folder to right place
        if (os.path.exists("../soh/assets/xml/" + rom.version.xml_ver + "/")):
            shutil.rmtree("../soh/assets/xml/" + rom.version.xml_ver + "/")
        shutil.copytree(tempXmlPath, "../soh/assets/xml/" + rom.version.xml_ver + "/")

        # build assets
        BuildOTR("../soh/assets/xml/" + rom.version.xml_ver + "/", rom_path, zapd_exe=args.zapd_exe)

        # copy xml_safe back to xml and remove temp xml folder
        shutil.rmtree("../soh/assets/xml")
        shutil.copytree("../soh/assets/xml_safe", "../soh/assets/xml")
        shutil.rmtree("../soh/assets/xml_safe")

        # remove temp xml folder
        shutil.rmtree(tempXmlPath)

if __name__ == "__main__":
    main()
