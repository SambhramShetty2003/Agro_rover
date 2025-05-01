import streamlit as st
import pandas as pd
import pickle

# Load the trained model
with open('soil_growth_model.sav', 'rb') as model_file:
    model = pickle.load(model_file)

# Load the dataset to get feature names
df = pd.read_csv('modified_plant_dataset (1).csv')
feature_columns = df.drop(columns=[df.columns[-1]]).columns.tolist()  # assuming last column is the target

# Initialize session state
if 'inputs' not in st.session_state:
    st.session_state.inputs = {}
if 'current_feature' not in st.session_state:
    st.session_state.current_feature = 0

st.title("🌾 Soil Growth Prediction System")
st.markdown("Enter one parameter at a time to predict plant growth performance.")

# Get the current feature name
if st.session_state.current_feature < len(feature_columns):
    feature = feature_columns[st.session_state.current_feature]
    
    # Determine input type
    if df[feature].dtype in ['float64', 'int64']:
        value = st.number_input(f"Enter value for **{feature}**:",
                                value=float(df[feature].mean()))
    else:
        value = st.selectbox(f"Select value for **{feature}**:",
                             options=df[feature].unique())

    if st.button("Next"):
        st.session_state.inputs[feature] = value
        st.session_state.current_feature += 1
        st.experimental_rerun()
else:
    # All features collected, show prediction
    st.success("✅ All inputs provided!")

    # Show collected inputs
    st.subheader("Entered Values:")
    st.write(pd.DataFrame([st.session_state.inputs]))

    # Predict
    input_df = pd.DataFrame([st.session_state.inputs])
    prediction = model.predict(input_df)[0]
    st.subheader("🌱 Predicted Growth Output:")
    st.success(f"**{prediction}**")

    # Option to restart
    if st.button("Reset"):
        st.session_state.inputs = {}
        st.session_state.current_feature = 0
        st.experimental_rerun()
