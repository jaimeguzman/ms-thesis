
# Code taken from wikipedia article

def bwt(s):
    """Apply Burrows-Wheeler transform to input string."""
    assert "\0" not in s, "Input string cannot contain null character ('\\0')"
    s += "\1"  # Add end of file marker
    table = sorted(s[i:] + s[:i] for i in range(len(s)))  # Table of rotations of string
    last_column = [row[-1:] for row in table]  # Last characters of each row
    return "".join(last_column)  # Convert list of characters into string

print bwt("BANNANA")
print bwt("BANANA")
print bwt("Hola mundo!")
print bwt("Juicy juice!")
print bwt("Esto es un paralelepipedo")
