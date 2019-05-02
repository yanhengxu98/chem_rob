import xlrd
import xlwt
from pdfminer.pdfinterp import PDFResourceManager, PDFPageInterpreter
from pdfminer.converter import TextConverter
from pdfminer.layout import LAParams
from pdfminer.pdfparser import PDFPage
from io import StringIO

chemicals = xlrd.open_workbook("chemicals.xlsx")
n = chemicals.sheets()[0].col_values(0)
chdict = []
for i in n:
    chdict.append(i.lower())

instruments = xlrd.open_workbook("instruments.xlsx")
n = instruments.sheets()[0].col_values(0)
indict = []
for i in n:
    indict.append(i.lower())


def unificate(inputargument):
    temp = inputargument.replace("*10-", "e-")
    if temp[-1] == ".": temp = temp[0:len(temp)-1]
    if temp[-1] == ",": temp = temp[0:len(temp) - 1]
    ## get rid of the last period or comma

    i = 0
    while i < len(temp):
        if temp[i] == "-":
            if temp[i-1] == "e":
                i += 1
                continue
            else:
                temp = temp[0:i] + temp[i+1:]
                continue
        i += 1

    for i in range(len(temp)):
        if (temp[i].isalpha() and temp[i] != "e") or temp[i] == "°":
            break
    numbpart = temp[0:i]
    unitpart = temp[i:]

    if is_conc(temp):
        ## M
        if unitpart == "M":
            return str(eval(numbpart))
        elif unitpart == "mM":
            return str(eval(numbpart) / 1000)
        else:
            return inputargument
    elif is_ijsp(temp):
        ## s-1
        if unitpart == "s-1":
            return str(eval(numbpart))
        elif unitpart == "min-1":
            return str(eval(numbpart) / 60)
        else:
            return inputargument
##    elif is_nrep(temp):
    elif is_rtsp(temp):
        ## rpm
        if unitpart == "rpm":
            return str(eval(numbpart))
        else:
            return inputargument
    elif is_temp(temp):
        ## °C
        if unitpart == "°C":
            return str(eval(numbpart))
        elif unitpart == "K":
            return str(eval(numbpart) + 273.15)
        else:
            return inputargument
    elif is_time(temp):
        ## s
        if unitpart == "s":
            return str(eval(numbpart))
        elif unitpart == "min":
            return str(eval(numbpart) * 60)
        elif unitpart == "h":
            return str(eval(numbpart) * 3600)
        else:
            return inputargument
    elif is_volm(temp):
        ## ml
        if unitpart == "ml" or unitpart == "mL":
            return str(eval(numbpart))
        elif unitpart == "L" or unitpart == "l":
            return str(eval(numbpart) * 1000)
        else:
            return inputargument
    elif is_weit(temp):
        ## g
        if unitpart == "g":
            return str(eval(numbpart))
        elif unitpart == "mg":
            return str(eval(numbpart) / 1000)
        elif unitpart == "kg":
            return str(eval(numbpart) * 1000)
        else:
            return inputargument


def convert_pdf_to_txt(path):
    
    rsrcmgr = PDFResourceManager()
    retstr = StringIO()
    codec = "utf-8"
    laparams = LAParams()
    device = TextConverter(rsrcmgr, retstr, codec = codec, laparams = laparams)
    fp = open(path, "rb")
    interpreter = PDFPageInterpreter(rsrcmgr, device)
    password = ""
    maxpages = 0
    caching = True
    pagenos = set()
    for page in PDFPage.get_pages(fp, pagenos,
                                  maxpages = maxpages,
                                  password = password,
                                  caching = caching,
                                  check_extractable = True):
        interpreter.process_page(page)
    fp.close()
    device.close()
    strings = retstr.getvalue().replace("\n\n", "\n")
    retstr.close()
    try:
        with open(path[0:-3] + "txt", "w", encoding="utf-8", errors="ignore") as f:
            f.write(strings)
##        print ("%s Writing Succeed!")
        f.close()
    except:
        print ("Writing Failed!")


def txt_extractor(path):
    file = open(path,
                "r", encoding="utf-8", errors="ignore")
    tempString = ""
    flag = False
    
##    if "particle-journal" in open(path, "r", encoding="utf-8", errors="ignore").read():
####        print("Particle Journal!")
##        for line in file:
##            if "Experimental Section" in line:
##                flag = True
##                print("start")
##            elif ("Acknowledgements" in line )or("Results and Discussion" in line):
##                flag = False
##                print("stop")
##                continue
##            if flag == True:
##                tempString += line.replace("\n\n", "\n")
##                
##    elif "pubs.acs.org/cm" in open(path, "r", encoding="utf-8", errors="ignore").read():
####        print("Chemistry of Materials!")
##        for line in file:
##            if "Experimental Section" in line:
##                flag = True
##                print("start")
##            elif ("Acknowledgements" or "Results") in line:
##                flag = False
##                print("stop")
##                continue
##            if flag == True:
##                tempString += line.replace("\n\n", "\n")

    for line in file:        
        if "Preparation of the Initial, CTAB-Capped Au Clusters" in line:
            flag = True
            continue
        elif "Standard Procedure for the Preparation of Au Nanospheres" in line:
            flag = False
            break
        if flag == True:
            tempString += line.replace("\n\n", "\n")
    
    expr = open(path[0:-4] + "_.txt",
                "w", encoding="utf-8", errors="ignore")
    expr.write(tempString)
    expr.close()
    file.close()


def is_prep(s):
    s = s.lower().replace("(", "").replace(")", "").replace(".", "")
    if s=="under" or s=="simultaneously":
        return True
    elif s=="both" or s=="seperate" or s=="and":
        return True
    elif s == "into":
        return True
    return False


def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass 
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass 
    return False


def is_num(i):
    i = i.replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if (("+" in i) and is_number(i.replace("+", "")))or(("," in i) and is_number(i.replace(",", ""))):
        return True
    elif (("-" in i) and is_number(i.replace("-", "")))or(("−" in i) and is_number(i.replace("−", ""))):
        return True
    elif is_number(i) or i == "*" or i == "-":
        return True
    return False


def is_pfix(i):
    if ("Mw" in i):
        return True
    return False


def is_post(i):
    i = i.lower().replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if (i == "mg")or(i == "g")or(i == "kg")or(i == "mmol")or(i == "mol"):
        return True
    elif (i == "μl")or(i == "ml")or(i == "mm")or(i == "m")or(i == "rpm")or(i == "°c")or(i == "k")or(i == "%"):
        return True
    elif (i == "s")or(("min" in i)and((i.replace(".", "") == "min") or (i.replace(",", "") == "min")))or(("h" in i)and((i.replace(".", "") == "h") or (i.replace(",", "") == "h"))):
        return True
    elif (i == "s-1")or(("min-1" in i)and((i.replace(".", "") == "min-1") or (i.replace(",", "") == "min-1"))):
        return True
    elif ("hour" in i)or(i == "times"):
        return True
    return False


def is_chem(i):
    if i.lower().replace(".", "").replace(",", "") in chdict: return True
    else:
        parts = i.split(" ")
        for j in parts:
            if not (j.lower().replace(".", "").replace(",", "") in chdict): return False
        return True


def is_inst(i):
    if i.lower().replace("(", "").replace(")", "").replace(".", "").replace(",", "") in indict: return True
    else:
        parts = i.split(" ")
        for j in parts:
            if not (j.lower().replace(".", "").replace(",", "") in indict): return False
        return True


def is_acts(i):
    i = i.lower().replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if ("boil" in i)or("stir" in i)or("left" in i)or("react" in i)or("quench" in i)or("inject" in i)or("dried" in i)or("dry" in i):
        return True
    elif("transparent" in i)or("heat" in i)or("store" in i)or("kept" in i)or("degas" in i)or("precipitate" in i)or("wash" in i)or("shak" in i)or("chill" in i):
        return True
    return False


def is_time(i):
    if (("s" in i) and is_num(i.replace("s", ""))) or (("min" in i) and is_num(i.replace("min", ""))) or (("h" in i) and is_num(i.replace("h", ""))):
        return True
    return False


def is_conc(i):
    if ("mM" in i)or( "M" in i):
        return True
    return False


def is_pure(i):
    if ("%" in i):
        return True
    return False


def is_volm(i):
    i = i.lower().replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if (("μl" in i)or( "ml" in i))and(not "min" in i):
        return True
    return False


def is_weit(i):
    i = i.replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if (("mg" in i) and is_num(i.replace("mg", "")))or(("g" in i) and is_num(i.replace("g", "")))or(("kg" in i) and is_num(i.replace("kg", ""))):
        return True


def is_temp(i):
    i = i.replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if (("°C" in i) and is_num(i.replace("°C", "")))or(("K" in i) and is_num(i.replace("K", "")))or("temperature" in i)or("room" in i):
        return True
    return False


def is_quan(i):
    i = i.replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if (("mmol" in i) and is_num(i.replace("mmol", "")))or(("mol" in i) and is_num(i.replace("mol", ""))):
        return True
    return False

def is_rtsp(i):
    i = i.replace("(", "").replace(")", "").replace(".", "").replace(",", "")
    if ("rpm" in i) and is_num(i.replace("rpm", "")):
        return True
    return False


def is_ijsp(i):
    if ("min-1" in i)or("s-1" in i)or("dropwise" in i):
        return True
    return False


def is_nrep(i):
    if ("times" in i)and(is_num(i.replace("times", ""))):
        return True
    return False


def is_cond(i):
    if "vacuum" in i:
        return True
    return False


def is_data(i):
    if is_time(i) or is_conc(i) or is_volm(i) or is_weit(i) or is_temp(i) or is_quan(i) or is_rtsp(i) or is_ijsp(i) or is_nrep(i):
        return True
    return False


def is_info(i):
    if is_num(i) or is_pfix(i) or is_post(i) or is_chem(i) or is_acts(i) or is_time(i) or is_data(i) or is_prep(i) or is_inst(i) or is_cond(i):
        return True
    return False


def trnc(string):
    return string.replace("(", "").replace(")", "").replace(".", "").replace(",", "")


def dfs(node, path):    
    for i in node.getchildren():
        path.append(i)
        path = dfs(i, path)        
    return path


def link(info):
    temp = []
    i = 0
    while i < len(info):
        if i == len(info)-1:
            temp.append(info[i])
            break
        else:
            if is_num(info[i]):
                index = i+1
                tempstring = info[i]
                while not is_post(info[index]):
                    tempstring += info[index]
                    index += 1
                tempstring += info[index]
                temp.append(tempstring)
                i = index + 1
                
            elif is_inst(info[i]):
                index = i+1
                tempstring = info[i]
                while is_inst(info[index]):
                    tempstring += info[index]
                    index += 1
                temp.append(tempstring)
                i = index

            elif is_temp(info[i]):
                index = i+1
                tempstring = info[i]
                while is_temp(info[index]):
                    tempstring += info[index]
                    index += 1
                temp.append(tempstring)
                i = index

            elif is_chem(info[i]):
                index = i+1
                tempstring = info[i]
                while True:
                    if is_chem(tempstring+info[index]):
                        tempstring += info[index]
                        index += 1
                    elif is_chem(tempstring+" "+info[index]):
                        tempstring += (" "+info[index])
                        index += 1
                    else:
                        temp.append(tempstring)
                        i = index
                        break
            elif is_acts(info[i]):
                temp.append(info[i])
                i += 1
            elif is_data(info[i]):
                temp.append(info[i])
                i += 1
            elif info[i] == "into":
                temp.append(info[i])
                i += 1
            else:
                i += 1

    return temp


def parse(temp):
    info = []
    index = 0
    into = 0
    while index < len(temp):
        print(temp[index])
        p = []
        if is_chem(temp[index]):
            ## chemical
            p.append(temp[index])
            j = index + 1
            if j >= len(temp): break
            chem = 1
            conc = 0
            volm = 0
            weit = 0
            while (not is_chem(temp[j])) and (not is_acts(temp[j])):
                if not is_prep(temp[j]):
                    if is_conc(temp[j]) or is_pure(temp[j]):
                        if conc == 0:
                            conc = 1
                    elif is_volm(temp[j]) and volm == 0:
                        volm = 1
                    elif is_weit(temp[j]) and weit == 0:
                        weit = 1
                    else:
                        break
                    p.append(temp[j].replace("(", "").replace(")", ""))                    
                    j += 1
                    if j >= len(temp): break
                elif temp[j] == "into":
                    into = 1
                    j += 1
                else:
                    j += 1
                    continue
            index = j - 1
            
        elif is_data(temp[index]):
            if (is_conc(temp[index]) or is_pure(temp[index])) or is_quan(temp[index]) or is_volm(temp[index]):
                ## chemical
                chem = 0
                conc = 0
                volm = 0
                weit = 0
                if (is_conc(temp[index]) or is_pure(temp[index])): conc = 1
                elif is_volm(temp[index]): volm = 1
                elif is_weit(temp[index]): weit = 1
                p.append(temp[index].replace("(", "").replace(")", ""))
                j = index + 1
                if j >= len(temp): break
                while True:
                    if is_inst(temp[j]):
                        p.append(temp[j])
                        index = j
                        break
                    elif is_chem(temp[j]):
                        if chem == 0:
                            p.append(temp[j])
                            chem = 1
                            j += 1
                        else:
                            index = j - 1
                            break
                    else:
                        if not is_prep(temp[j]):
                            if (is_conc(temp[j]) or is_pure(temp[j])) and conc == 0: conc = 1
                            elif is_volm(temp[j]) and volm == 0: volm = 1
                            elif is_weit(temp[j]) and weit == 0: weit = 1
                            elif is_ijsp(temp[j]): ijsp = 1
                            else:
                                index = j - 1
                                break
                            p.append(temp[j].replace("(", "").replace(")", ""))
                            j += 1
                            if j >= len(temp):
                                index = j - 1
                                break
                        else:
                            j += 1
                            continue
                                
            elif len(temp[index]) == 1: info[len(info)-1].append(temp[index])
                
        elif is_acts(temp[index]):
            ## operation
            p.append(temp[index])
            j = index + 1
            if j >= len(temp): break
            while True:
                if ("wash" in temp[index]) and (is_conc(temp[j]) or is_quan(temp[j]) or is_volm(temp[j]) or is_acts(temp[j])):
                    index = j - 1
                    break
                elif (not "wash" in temp[index]) and (is_chem(temp[j]) or is_pure(temp[j]) or is_conc(temp[j]) or is_quan(temp[j]) or is_volm(temp[j]) or is_acts(temp[j])):
                    index = j-1
                    break
                else:
                    if not is_prep(temp[j]):
                        p.append(temp[j].replace("(", "").replace(")", ""))
                        j += 1
                        if j >= len(temp):
                            index = j - 1
                            break
                    else:
                        break            
        index += 1

        if p != []:
            info.append(p)
            if into == 1:
                info.append(["into"])
                into = 0
    print(info)

    for i in range(len(info)):
        if i < len(info):
            if len(info[i]) == 1:
                if is_chem(info[i][0]):
                    info.remove(info[i])
                else:
                    i += 1
                    continue

    for i in range(len(info)):
        if i < len(info):
            if is_chem(info[i][0]) or is_data(info[i][0]):
                check = info[i]
                volm = 0
                for j in check:
                    if is_volm(j): volm = 1
                if volm == 0:
                    ## START
                    last = i - 1
                    for k in range(len(info[last])):
                        if is_volm(info[last][k]): break
                    volmvalue = info[last][k]
                    ## find the volume
                    numbpart = ""
                    unitpart = ""
                    for l in volmvalue:
                        if l.isdigit(): numbpart += l
                        elif l.isalpha(): unitpart += l
                    newvolm = str(float(numbpart)/2) + unitpart
                    info[last][k] = newvolm
                    info[i].append(newvolm)
                    ## volume / 2

                    for j in range(len(info[last])):
                        if is_conc(info[last][j]):
                            numbpart = ""
                            unitpart = ""
                            for l in info[last][j]:
                                if (not l.isalpha()) and l!="(" and l!=")": numbpart += l
                                else: unitpart += l
##                            print(numbpart, unitpart)
                            newconc = str(float(numbpart.replace("*10-", "e-"))*2) + unitpart
                            info[last][j] = newconc

                            for k in range(len(info[i])):
                                if is_conc(info[i][k]):
                                    numbpart = ""
                                    unitpart = ""
                                    for l in info[i][k]:
                                        if (not l.isalpha()) and l!="(" and l!=")": numbpart += l
                                        else: unitpart += l
                                    newconc = str(float(numbpart.replace("*10-", "e-"))*2) + unitpart
                                    info[i][k] = newconc
                                ## conc * 2
                    info[last] = [info[last], info[i]]
                    info.remove(info[i])

    info_ = []
    i = 0
    while i < len(info):
        if info[i] != ["into"]:
            info_.append(info[i])
            i += 1
            
        else:
            info_.insert(i-1, info[i+1])
            i += 2
            
    info = []
    for i in info_:
        if type(i[0]) == list:
            for j in i:
                info.append(j)
        else:
            info.append(i)    
    
    return info


def xls_gen(acts, path):
    file = xlwt.Workbook(encoding = "utf-8")
    sheet = file.add_sheet("PROCEDURES")
    row0 = []
    row1 = []

    nforpump = 0
    for act in acts:
        if is_chem(act[0]) or is_data(act[0]):
            ## describing the chemicals
        
            for i in act:
                if is_chem(i):
                    row1.append(i)
                    row0.append("chemical in pump " + str(nforpump))
                    nforpump += 1
            if len(row1)%4 == 0: continue
            
            for i in act:
                if is_conc(i) or is_pure(i): row1.append(unificate(i))
            if len(row1)%4 == 1: row1.append(" ")
            row0.append("concentration"+str(nforpump))
            
            for i in act:
                if is_volm(i): row1.append(unificate(i))
            if len(row1)%4 == 2: row1.append(" ")
            row0.append("volume"+str(nforpump))

            for i in act:
                if is_weit(i): row1.append(unificate(i))
            if len(row1)%4 == 3: row1.append(" ")
            row0.append("weight"+str(nforpump))

    nforstep = 0
    for act in acts:
        ## steps
        
        if is_chem(act[0]) or is_data(act[0]):           
            if is_inst(act[1]):
                ## transfer
                row0 += ["Step " + str(nforstep), "To"]
                row1 += ["Transfer", "".join(act)]
                nforstep += 1
            else:
                ## addition            
                for i in act:
                    if is_chem(i): row1 += ["Addition", i]
                row0 += ["Step " + str(nforstep), "chemical"] ## requires number of the pump
                nforstep += 1
                
                for i in act:
                    if is_volm(i):
                        row1.append(unificate(i))
                        row0.append("volume")
                    elif is_weit(i):
                        row1.append(unificate(i))
                        row0.append("weight")
                    elif is_ijsp(i):
                        row1.append(unificate(i))
                        row0.append("injection speed")

        elif is_acts(act[0]):
            ## operations
            
            for i in act:
                if is_acts(i):
                    i = i.lower()
                    row0.append("Step " + str(nforstep))
                    nforstep += 1
                    if ("heat" in i): row1.append("Heat")
                    elif ("react" in i)or("left" in i)or("kept" in i):
                        row1.append("Wait")
                    elif "boil" in i: row1.append("Heat to boiling")
                    elif ("stir" in i)or("shak" in i): row1.append("Stir")
                    elif ("store" in i): row1.append("Store")
                    elif ("inject" in i): row1.append("Injection")
                    elif ("wash" in i): row1.append("Wash")
                    elif ("dried" in i)or("dry" in i): row1.append("Dry")
                    elif ("chil" in i): row1.append("Chill")
                        
                elif is_temp(i):
                    row1.append(unificate(i))
                    row0.append("Temperature")
                elif is_time(i):
                    row1.append(unificate(i))
                    row0.append("Time")
                elif is_time(i.replace(".", "")):
                    row1.append(i.replace(".", ""))
                    row0.append("Time")
                elif is_rtsp(unificate(i)):
                    row1.append(i)
                    row0.append("Rotation Speed")
                elif is_ijsp(unificate(i)):
                    row1.append(i)
                    row0.append("Injection Speed")
                elif is_chem(i):
                    row1.append(i)
                    row0.append("With")
                elif is_nrep(i):
                    row1.append(i)
                    row0.append("For")
                elif is_cond(i):
                    row1.append(i)
                    row0.append("Under") 

    for i in range(len(row0)):
        print(row0[i], ":", row1[i])

    for i in range(len(row0)):
        sheet.write(0, i, row0[i])
        sheet.write(1, i, row1[i])
    file.save(path.replace("txt", "xls"))

    return [row0,row1]


def run(path):
    if path == "EXIT": return
    elif path[-3:] == "pdf":
        text = convert_pdf_to_txt(path)
        expr = txt_extractor(path[0:-3] + "txt")
        file = open(path[0:-4] + "_.txt", "r", encoding = "utf-8")
        text = ("".join(file.readlines())).replace("\n", "").replace(",", "").replace("−", "-").replace("×", "*").split(" ")
        file.close()
        #print(text)
        temp = []
        for i in text:
            if is_info(i): temp.append(i)
        #print(temp)
        temp = link(temp)
        #print(temp)        
        acts = parse(temp)
        #print(acts)
        #print()
        xls_gen(acts, path.replace("pdf", "txt"))
    elif path[-3:] == "txt":
        file = open(path, "r", encoding = "utf-8")
        text = ("".join(file.readlines())).replace("\n", "").replace(",", "").replace("−", "-").replace("×", "*").split(" ")
        file.close()
        #print(text)
        temp = []
        for i in text:
            if is_info(i): temp.append(i)
        #print(temp)
        temp = link(temp)
        #print(temp)        
        acts = parse(temp)
        #print(acts)
        #print()
        xls_gen(acts, path)

        a = xls_gen(acts, path)
        return a


run('2.txt')


