import pandas as pd
df = pd.read_csv('text_files/ME11_plus_new.txt',sep="\t")
def modify_last_digit(n):
    n_str = str(n)
    if len(n_str) > 1:
        # Replace the last digit with the second last digit
#        modified_str = n_str[:-1] + n_str[-2]
        modified_str = n_str[:2]+'4'+n_str[3:]
        return int(modified_str)
    else:
        # If there's only one digit, return it as is
        return n

# Apply the function to the 'rhid' column
df['rhid'] = df['rhid'].apply(modify_last_digit)
print(df)
f  = 'ME11a_plus.txt' 
df.to_csv(f, sep="\t", index=False)
