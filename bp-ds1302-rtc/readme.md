# Catatan Tentang DS1302 RTC

#### **24 Juli 2020**

1. Pembacaan belum stabil, output date/time masih berubah-ubah tiap loopnya.
2. Library yang dipake yaitu [RTClib NeiroNx](https://github.com/NeiroNx/RTCLib)
   - Di file .h nya perlu diubah dari `Wire1` ke `Wire`
