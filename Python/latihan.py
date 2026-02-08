# Soal 7

nilai_tugas = [70, 80, 65, 85, 75]
print(f"nilai tugas:{nilai_tugas}")
# menghapus nilai tertinggi dan terendah

nilai_tugas.remove(max(nilai_tugas))
nilai_tugas.remove(min(nilai_tugas))
print(f"nilai tugas setelah nilai tertinggi dan terendah dihapus: {nilai_tugas}")

rata_rata = sum(nilai_tugas)/len(nilai_tugas)
print(f"rata rata nilai tugas setelah dihapus: {rata_rata}")

nilai_tugas.sort()
print(f"nilai setelah diurut: {nilai_tugas}")
