class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        close = {
         ']':'[',
         '}':'{',
         ')':   '(',
        }
               
        for char in s:
            if char in '({[':
                stack.append(char)
            else:
                expect_match = close[char]
                got_match = stack and stack.pop()
                if expect_match != got_match: 
                    return False
        return not stack