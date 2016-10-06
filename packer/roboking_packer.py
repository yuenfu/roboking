import os
import sys
import struct 

class MainHeader:
	def __init__(self,sub_data):
		self.unRevision = ""
		self.unFirmwareSize = ""
		self.unChecksum = ""
		self.szPartNumber = ""
		self.sub_data = sub_data

		self.set_data()

	def set_data(self):
		self.unRevision = "\x5e\x3f" # ??
		self.unFirmwareSize = len(self.sub_data)
		self.unChecksum = self.get_checksum()
		self.szPartNumber = self.get_part_num()
	
	def get_checksum(self):
		pass

	def get_part_num(self):
		pass

	def view(self):
		pass

class SubHeader:
	def __init__(self, path):
		self.unDataSize	= ""
		self.unPathLength = ""
		self.unFlag = "\x00\x00"		
		self.file_name = ""
		self.data = ""

		self.set_data(path)

	def set_data(self, path):
		self.file_name = path[path.find("/"):]
		self.unPathLength = len(self.file_name)
		if os.path.isfile(path):
			with open(path, "rb") as f:
				self.data = f.read()
		else:
			self.data = ""
		self.unDataSize = len(self.data)
		

	def create_form(self):
		data = ""
		data += struct.pack("<L", self.unDataSize)
		data += struct.pack("<H", self.unPathLength)
		data += self.unFlag
		data += self.enc(self.file_name)
		data += self.enc(self.data)	
		return data

	def enc(self, data):
		ret_data = ""
		for i in data:
			if ord(i) >= 0x80:
				ret_data += struct.pack("<B", (ord(i) - 0x80 & 0xff))
			else:
				ret_data += struct.pack("<B", (~ord(i) & 0xff))
		return ret_data

	def view(self):
		print "[+] File name : " +self.file_name
		print "[+] unDataSize : " + str(self.unDataSize)
		print "[+] unPathLength : " + str(self.unPathLength)
		print "[+] unFlag : " + self.unFlag
		print "[+] Data : " + self.data[:10]
		print "\n"

class Packer:
	def __init__(self, path):
		self.m = MainHeader()
		self.p_dir = []
		self.p_file = []
		self.file_search(path)
	
	def file_search(self, path):
		try:
			files = os.listdir(path)
			for file in files:
				full_path = os.path.join(path, file)
				if os.path.isdir(full_path):
					self.p_dir.append(full_path)
					self.file_search(full_path)
				else:
					self.p_file.append(full_path)
		except:
			print "Except"

	def create_pack_data(self):
		# Main Header
		# Sub Headers
		sub_header = ""
		for file in self.get_file_list():
			s = SubHeader(file)
			s.view()
			sub_header += s.create_form()
		f = open("r", "wb")
		f.write(sub_header)
		f.close()

	def get_file_list(self):
		return self.p_dir + self.p_file

p = Packer(sys.argv[1])
p.create_pack_data()
