#xgettext --keyword=_ --keyword="_P:1,2" --language=C --from-code=UTF-8 -o ../infclass-translation/infclasspot.po $(find ./src -name \*.cpp -or -name \*.h)

import sys, polib, json, os

reload(sys)
sys.setdefaultencoding('utf-8')

def ConvertPo2Json(languageCode, plurals):
	if os.path.isfile("../infclass-translation/infclasspot_"+languageCode+".po"):
		poFileName = "../infclass-translation/infclasspot_"+languageCode+".po"
		jsonFileName = "./languages/"+languageCode+".json"

		po = polib.pofile(poFileName)

		f = file(jsonFileName, "w")

		print >>f, '{"translation":['

		for entry in po:
			if entry.msgstr:
				print >>f, '\t{'
				print >>f, '\t\t"key": '+json.dumps(str(entry.msgid))+','
				print >>f, '\t\t"value": '+json.dumps(str(entry.msgstr))+''
				print >>f, '\t},'
			elif entry.msgstr_plural.keys():
				print >>f, '\t{'
				print >>f, '\t\t"key": '+json.dumps(str(entry.msgid_plural))+','
				for index in sorted(entry.msgstr_plural.keys()):
					print >>f, '\t\t"'+plurals[index]+'": '+json.dumps(entry.msgstr_plural[index])+','
				print >>f, '\t},'

		print >>f, ']}'

ConvertPo2Json("cn-sim", ["other"])
ConvertPo2Json("cn-tra", ["other"])
