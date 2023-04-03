import {createSlice, PayloadAction} from '@reduxjs/toolkit';

interface QuestionEventState {
    visible: boolean
    data: {name: string, symbol: string[]}[]
}

const initialQuestionEvent: QuestionEventState = {
    visible: false,
    data: []
}

export const questionEventSlice = createSlice({
    name: 'questionEvent',
    initialState: initialQuestionEvent,
    reducers: {
        setVisible(state, action: PayloadAction<boolean>) {
            state.visible = action.payload
        }
    }
})

export default questionEventSlice.reducer;