import streamlit as st
import pandas as pd
import sqlite3
import pandas_profiling
from streamlit_pandas_profiling import st_profile_report

menus = ['Tables', 'Coins', 'Spot', 'Futures']
select = st.sidebar.selectbox('Chọn chức năng', menus)
if select == menus[0]:
    tables = ['Coins', 'CoinHistory', 'Categories', 'Transactions', 'Futures']
    select2 = st.selectbox('Chọn bảng', tables)
    if select2 == tables[0]:
        conn = sqlite3.connect('crypto.sqlite3')
        coins_df = pd.read_sql_query("SELECT * FROM Coins", conn)
        coins_df = coins_df.astype({'ID':str, 'Name':str, 'Symbol':str, 'Date':'datetime64[ns]'})
        conn.close()
        st.dataframe(coins_df.sample(100))
        if st.button('Profile Report'):
            st_profile_report(coins_df.profile_report(minimal=True))
    elif select2 == tables[1]:
        conn = sqlite3.connect('crypto.sqlite3')
        coinHistory_df = pd.read_sql_query("SELECT * FROM CoinHistory", conn)
        coinHistory_df = coinHistory_df.astype({'ID':str, 'Date':'datetime64[ns]'})
        conn.close()
        st.dataframe(coinHistory_df.sample(100))
        if st.button('Profile Report'):
            st_profile_report(coinHistory_df.profile_report(minimal=True))
    elif select2 == tables[2]:
        conn = sqlite3.connect('crypto.sqlite3')
        categories_df = pd.read_sql_query("SELECT * FROM Categories", conn)
        categories_df = categories_df.astype({'Type':str, 'Name':str, 'Description':str})
        conn.close()
        st.dataframe(categories_df)
    elif select2 == tables[3]:
        conn = sqlite3.connect('crypto.sqlite3')
        transactions_df = pd.read_sql_query("SELECT * FROM Transactions", conn)
        transactions_df = transactions_df.astype({'Date':'datetime64[ns]', 'InCoinID':str, 'OutCoinID':str, 'FeeCoinID':str, 'Exchange':str, 'Note':str})
        conn.close()
        st.dataframe(transactions_df.sample(100))
        if st.button('Profile Report'):
            st_profile_report(transactions_df.profile_report(minimal=True))
    else:
        conn = sqlite3.connect('crypto.sqlite3')
        futures_df = pd.read_sql_query("SELECT * FROM Futures", conn)
        futures_df = futures_df.astype({'CoinID':str, 'Mode':str, 'Type':str, 'Date':'datetime64[ns]', 'Exchange':str, 'Note':str})
        conn.close()
        st.dataframe(futures_df.sample(100))
        if st.button('Profile Report'):
            st_profile_report(futures_df.profile_report(minimal=True))
elif select == menus[1]:
    conn = sqlite3.connect('crypto.sqlite3')
    coins_name_df = pd.read_sql_query("SELECT id, name || ' (' || upper(symbol) || ')' as Name FROM Coins", conn).astype({'ID':str, 'Name':str})
    conn.close()
    coins_name_df = coins_name_df.values.tolist()
    select2 = st.selectbox('Chọn coin', coins_name_df, format_func=lambda x: x[1])[0]

    conn = sqlite3.connect('crypto.sqlite3')
    coin_history_df = pd.read_sql_query(f"SELECT date, price, volume, marketcap FROM CoinHistory WHERE id = '{select2}'", conn).astype({'Date':'datetime64[ns]'})
    coin_history_df = coin_history_df.set_index('Date')
    conn.close()
    st.dataframe(coin_history_df)
    if st.button('Profile Report'):
        st_profile_report(coin_history_df.profile_report(minimal=False))
    if st.button('Graph'):
        graphs = ['Price', 'Volume', 'Market Cap']
        st.line_chart(coin_history_df.Price)
        st.line_chart(coin_history_df.Volume)
        st.line_chart(coin_history_df.MarketCap)
elif select == menus[2]:
    st.title('Current Balance')
    conn = sqlite3.connect('crypto.sqlite3')
    InOut_df = pd.read_sql_query(f"SELECT id, symbol, TotalQty as Amount, Price as 'Price (USD)', TotalQty * Price as 'Value (USD)' FROM InOut", conn).astype({'ID':str, 'Symbol':str}).dropna().set_index('ID')
    conn.close()
    st.dataframe(InOut_df)

    total_value = InOut_df['Value (USD)'].sum()
    imin = InOut_df['Value (USD)'].min()
    imax = InOut_df['Value (USD)'].max()

    st.write('Summary')
    st.write(f'Total transactions: {InOut_df.shape[0]}')
    st.write(f'Hold: {InOut_df.Amount[InOut_df.Amount > 0].count()} coins')
    st.write(f'All Time Profit: {total_value} $')
    st.write(f'Best Performer: {imax} $')
    st.write(f'Worst Performer: {imin} $')
else:
    conn = sqlite3.connect('crypto.sqlite3')
    Futures_df = pd.read_sql_query(f"SELECT * FROM Futures", conn).astype({'CoinID':str, 'Mode':str, 'Type':str, 'Date':'datetime64[ns]', 'Exchange':str, 'Note':str}).set_index('ID')
    conn.close()
    st.dataframe(Futures_df)
    st.write(f'All Time Profit: {Futures_df.PNL.sum() - Futures_df.Fee.sum()} $')
    st.write(f'RR min: {Futures_df.RR.min()}')
    st.write(f'RR max: {Futures_df.RR.max()}')
    st.write(f'Total Volume: {Futures_df.Margin.sum()} $')
    st.write(f'Winrate: {(Futures_df.PNL > 0).mean()}')