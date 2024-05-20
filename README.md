# ukvm_arduino_serial

# How to use

When sending serial data to the Arduino using this class, you have to encapsulte the data in an open tag and close tag, which are "<" for open and ">" for close.

### Example

```c++
sendToArduino("<Hello Arduino>")
```

This class will give you "Hello Arduino" without the "<" and ">" tags.