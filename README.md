﻿# RUNNING MAN!!!
## GIỚI THIỆU CHUNG:
> Họ và tên: Phạm Quốc Anh
>
> K67J-CN16-UET
>
> MSV: 22026546

- Đây là bài tập lớn cuối kì môn lập trình nâng cao của mình, một sản phẩm game đầu tay.

![Screenshot (33)](https://i.imgur.com/RA8Xxyf.png)



- **Running Man!** được hoàn thành dựa trên lối chơi của Google Dinosaur và Rambo nhưng đã sửa đổi đôi chút về cách chơi theo ý tưởng, mong ước của bản thân để mang lại một con game tốt hơn.

Game được viết bằng ngôn ngữ C++ và sử dụng thư viện SDL2

## MÔ TẢ GAME:

- **Nhiệm vụ của người chơi là nhập vai vào nhân vật Among Us , hãy cùng đưa cậu ấy vượt qua những thử thách nguy hiểm đáng sợ để đến phi thuyền trốn thoát khỏi hành tinh đầy quái vật đáng sợ:**
  - Nhấn SPACE để nhảy lên vượt qua những cạm bẫy nguy hiểm
  
  - Nhấn <- || ->  để di chuyển sang trái hoặc phải
  
  - Nhấn **PLAY GAME** để bắt đầu cuộc hành trình
  
- **Điểm của người chơi sẽ là số Coin thu được trong một lượt đấu** 

- **Người chơi sẽ có 3 mạng để chơi!!!**

- **Hãy đưa Ú đến với chiến thắng nào và mang về thật nhiều coin nào!!**
## CÁCH CÀI ĐẶT:

- Tải xuống tại đây: [Download](https://github.com/anhquocuet/Running-Man.git) 
- Nếu bạn đã cài đặt đẩy đủ các thư viện sdl2 và makefile vào vscode.
##### Hướng dẫn cái đặt theo cách khác:
- B1: Cài [Vscode](https://code.visualstudio.com/download) và [SDL2](https://lazyfoo.net/tutorials/SDL/)
- B2: Cài [Debug](https://code.visualstudio.com/Docs/editor/debugging) cho vscode
- B3: Tạo một folder để git clone về
```
    git clone https://github.com/anhquocuet/Running-Man.git
```
## MÔ TẢ CHỨC NĂNG

- **Có hệ thống menu:**
  - Menu bắt đầu
  - Menu EndGame: GameOver và YouWin
  - Hỏi **RETRY** và **EXIT** khi endgame 
- **Có hệ thống âm thanh sinh động:**
  - Nhạc nền 
  - Nhạc hiệu ứng(SFX): khi player die
- **Có tính điểm và lưu điểm cao nhất sau mỗi lần chơi**
- **Có số lượng mạng nhất định để chơi**
- **Khi nhảy xuống hố hoặc va chạm với quái vật thì sẽ trừ mạng**
- **Khi mất 3 mạng thì sẽ gameover, nếu đi đến đích là sẽ CHIẾN THẮNG**
- **Đồ hoạ sinh động, đẹp**

## CÁC KĨ THUẬT LẬP TRÌNH ĐƯỢC SỬ DỤNG ##

- Mảng
- Con trỏ/ Giải phóng bộ nhớ
- Class
- Đồ hoạ
- Bắt sự kiện bàn phím, chuột
- Bắt va chạm per-pixel theo từng hoạt ảnh, chuyển động
- Stringstream
- Xử lý nhảy/ rơi theo vật lý
- Chia file theo đối tượng
- Đọc, ghi file
- Kĩ thuật tile map

## HỌC TẬP VÀ TÀI LIỆU THAM KHẢO:

- [Phát Triển Phần Mềm 123AZ](https://phattrienphanmem123az.com/)
- [Lazy Foo' Productions](https://lazyfoo.net/tutorials/SDL/)

## KẾT LUẬN

Hướng phát triển: Em sẽ cải tiến thêm các tuỳ chọn về map, nhân vật, âm thanh trong tương lai và cũng nghiên cứu cách khắc phục sự thiếu xót về khoảng cách va chạm.

Qua thời gian làm game, em đã cải thiện được một số kĩ năng về lập trình, tìm kiếm thông tin trên mạng, giải quyết vấn đề và về khả năng đọc hiểu tài liệu, khả năng sáng tạo, tư duy logic.

## CREDIT

**Em muốn gửi lời cảm ơn đến:**

- Thầy Trần Quốc Long
- Thầy Tạ Việt Cường
- Thầy Lê Đức Trọng
- Thầy Đỗ Minh Khá

Vì đã giúp em hoàn thành bài tập lớn này.
